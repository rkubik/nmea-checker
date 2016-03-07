#include "ireader.hpp"

#include <functional>
#include <memory>

struct NmeaStats
{
    size_t num_checksum;
    size_t num_corrupt;
    size_t num_empty;
    size_t num_sentences;
    size_t num_unknown;
};

class NmeaStreamer
{
public:
    NmeaStreamer(void);

    /**
     * Returns false if a sentence is corrupt or fails checksum test.
     *
     * @return true if no errors, false otherwise.
     */
    bool start(void);

    /**
     * Reset class to default settings (statistics and settings).
     */
    void reset(void);

    /**
     * Set reader.
     */
    void set_reader(IReader *reader);

    /**
     * Set flag to stop on first error.
     */
    void stop_on_error(void);

    /**
     * Set callback when program finishes.
     *
     * @param NmeaStats statistics
     */
    void on_done(std::function<void(const NmeaStats &)> cb);

    /**
     * Set callback on failed checksum.
     *
     * @param size_t line number
     * @param string NMEA sentence
     */
    void on_fail_checksum(std::function<void(size_t, const std::string &, uint8_t)> cb);

    /**
     * Set callback on corrupt sentence.
     *
     * @param size_t line number
     * @param string NMEA sentence
     */
    void on_fail_corrupt(std::function<void(size_t, const std::string &)> cb);

    /**
     * Set callback on empty sentences.
     *
     * @param size_t line number
     */
    void on_empty(std::function<void(size_t)> cb);

    /**
     * Set callback on valid sentence.
     *
     * @param size_t line number
     * @param string NMEA sentence
     */
    void on_valid(std::function<void(size_t, const std::string &)> cb);

    /**
     * Set callback on any line.
     *
     * @param size_t line number
     * @param string NMEA sentence
     */
    void on_line(std::function<void(size_t, const std::string &)> cb);

    /**
     * Set callback on any failure.
     *
     * @param size_t line number
     * @param string NMEA sentence
     */
    void on_fail(std::function<void(size_t, const std::string &)> cb);

    /**
     * Set callback on unknown NMEA sentences.
     *
     * @param size_t line number
     * @param string NMEA sentence
     */
    void on_unknown(std::function<void(size_t, const std::string &)> cb);

protected:
    /* Callback stubs */
    void event_done(const NmeaStats &stats) {}
    void event_fail(size_t, const std::string &) {}
    void event_fail_checksum(size_t, const std::string &, uint8_t) {}
    void event_fail_corrupt(size_t, const std::string &) {}
    void event_empty(size_t) {}
    void event_valid(size_t, const std::string &) {}
    void event_line(size_t, const std::string &) {}
    void event_unknown(size_t, const std::string &) {}

private:
    void record_checksum(const std::string &message);
    void record_corrupt(const std::string &message);
    void record_error(const std::string &message);

    bool stop_on_error_, has_error_;
    NmeaStats stats_;
    std::unique_ptr<IReader> reader_;

    std::function<void(const NmeaStats &)> on_done_;
    std::function<void(size_t, const std::string &)> on_fail_;
    std::function<void(size_t, const std::string &, uint8_t)> on_fail_checksum_;
    std::function<void(size_t, const std::string &)> on_fail_corrupt_;
    std::function<void(size_t)> on_empty_;
    std::function<void(size_t, const std::string &)> on_valid_;
    std::function<void(size_t, const std::string &)> on_line_;
    std::function<void(size_t, const std::string &)> on_unknown_;
};
