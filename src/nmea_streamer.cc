#include "nmea_streamer.hpp"
#include "minimea.hpp"
using namespace std;

NmeaStreamer::NmeaStreamer(void)
{
    reset();
}

void NmeaStreamer::on_done(function<void(const NmeaStats &)> cb)
{
    on_done_ = cb;
}

void NmeaStreamer::on_fail_checksum(function<void(size_t, const string &, uint8_t)> cb)
{
    on_fail_checksum_ = cb;
}

void NmeaStreamer::on_fail_corrupt(function<void(size_t, const string &)> cb)
{
    on_fail_corrupt_ = cb;
}

void NmeaStreamer::on_empty(function<void(size_t)> cb)
{
    on_empty_ = cb;
}

void NmeaStreamer::on_valid(function<void(size_t, const string &)> cb)
{
    on_valid_ = cb;
}

void NmeaStreamer::on_line(function<void(size_t, const string &)> cb)
{
    on_line_ = cb;
}

void NmeaStreamer::on_fail(function<void(size_t, const string &)> cb)
{
    on_fail_ = cb;
}

void NmeaStreamer::on_unknown(function<void(size_t, const string &)> cb)
{
    on_unknown_ = cb;
}

void NmeaStreamer::stop_on_error(void)
{
    stop_on_error_ = true;
}

void NmeaStreamer::set_reader(IReader *reader)
{
    reader_.reset(reader);
}

void NmeaStreamer::reset(void)
{
    on_done(bind(&NmeaStreamer::event_done, this, placeholders::_1));
    on_fail_checksum(bind(&NmeaStreamer::event_fail_checksum, this, placeholders::_1, placeholders::_2, placeholders::_3));
    on_fail_corrupt(bind(&NmeaStreamer::event_fail_corrupt, this, placeholders::_1, placeholders::_2));
    on_empty(bind(&NmeaStreamer::event_empty, this, placeholders::_1));
    on_valid(bind(&NmeaStreamer::event_valid, this, placeholders::_1, placeholders::_2));
    on_line(bind(&NmeaStreamer::event_line, this, placeholders::_1, placeholders::_2));
    on_fail(bind(&NmeaStreamer::event_fail, this, placeholders::_1, placeholders::_2));
    on_unknown(bind(&NmeaStreamer::event_unknown, this, placeholders::_1, placeholders::_2));

    stop_on_error_ = false;
    has_error_ = false;

    stats_.num_checksum = 0;
    stats_.num_corrupt = 0;
    stats_.num_sentences = 0;
    stats_.num_empty = 0;
    stats_.num_unknown = 0;
}

void NmeaStreamer::record_checksum(const string &message)
{
    record_error(message);
    stats_.num_checksum++;
    on_fail_checksum_(stats_.num_sentences, message,
                      minmea_checksum(message.c_str()));
}

void NmeaStreamer::record_corrupt(const string &message)
{
    record_error(message);
    stats_.num_corrupt++;
    on_fail_corrupt_(stats_.num_sentences, message);
}

void NmeaStreamer::record_error(const string &message)
{
    on_fail_(stats_.num_sentences, message);
    has_error_ = true;
}

bool NmeaStreamer::start(void)
{
    do {
        const string message = reader_->read_line();

        stats_.num_sentences++;

        on_line_(stats_.num_sentences, message);

        if (message.empty()) {
            stats_.num_empty++;

            on_empty_(stats_.num_sentences);

            continue;
        }

        if (!minmea_check(message.c_str(), false)) {
            record_checksum(message);
            continue;
        }

        switch (minmea_sentence_id(message.c_str(), false)) {
            case MINMEA_SENTENCE_RMC: {
                struct minmea_sentence_rmc frame;
                if (!minmea_parse_rmc(&frame, message.c_str())) {
                    record_corrupt(message);
                    continue;
                }
            } break;

            case MINMEA_SENTENCE_GGA: {
                struct minmea_sentence_gga frame;
                if (!minmea_parse_gga(&frame, message.c_str())) {
                    record_corrupt(message);
                    continue;
                }
            } break;

            case MINMEA_SENTENCE_GSV: {
                struct minmea_sentence_gsv frame;
                if (!minmea_parse_gsv(&frame, message.c_str())) {
                    record_corrupt(message);
                    continue;
                }
            } break;

            case MINMEA_SENTENCE_GSA: {
                struct minmea_sentence_gsa frame;
                if (!minmea_parse_gsa(&frame, message.c_str())) {
                    record_corrupt(message);
                    continue;
                }
            } break;

            case MINMEA_SENTENCE_GLL: {
                struct minmea_sentence_gll frame;
                if (!minmea_parse_gll(&frame, message.c_str())) {
                    record_corrupt(message);
                    continue;
                }
            } break;

            case MINMEA_SENTENCE_GST: {
                struct minmea_sentence_gst frame;
                if (!minmea_parse_gst(&frame, message.c_str())) {
                    record_corrupt(message);
                    continue;
                }
            } break;

            case MINMEA_UNKNOWN: {
                stats_.num_unknown++;
                on_unknown_(stats_.num_sentences, message);
                continue;
            } break;

            default: {
                record_corrupt(message);
                continue;
            } break;
        }

        on_valid_(stats_.num_sentences, message);
    } while (!(stop_on_error_ && has_error_) && !reader_->done());

    on_done_(stats_);

    return has_error_;
}
