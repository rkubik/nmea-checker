#include "valid_command.hpp"
#include "string_reader.hpp"
#include "serial_reader.hpp"
#include "file_reader.hpp"

#include <string>
using namespace std;

ValidCommand::ValidCommand(void)
{
    desc_.add_options()
        ("file,f", po::value<string>(), "File input")
        ("serial,d", po::value<string>(), "Serial input")
        ("sentence,s", po::value<string>(), "Sentence input")
        ("stat-format,t", po::value<string>()->default_value("Total: %t%n  Corrupt: %c%n  Checksum: %s%nError Rate: %e%n"), "Stats output format")
        ("line-format,l", po::value<string>()->default_value("%l %n (%e)%n"), "Stats output format")
        ("error,e", "Stop on first error")
    ;
}

bool ValidCommand::execute(void)
{
    const bool stop_on_error = vm_.count("error");
    if (vm_.count("file")) {
        return execute(new FileReader(vm_["file"].as<string>()), stop_on_error);
    } else if (vm_.count("serial")) {
        return execute(new SerialReader(vm_["serial"].as<string>()), stop_on_error);
    } else if (vm_.count("sentence")) {
        return execute(new StringReader(vm_["sentence"].as<string>()), stop_on_error);
    }
    return usage("Must choose at least one input");
}

bool ValidCommand::execute(IReader *reader, bool stop_on_error)
{
    bool valid = true;
//     size_t line_no = 0,
//            num_corrupt = 0,
//            num_bad_checksum = 0,
//            num_sentences = 0;
// 
//     do {
//         const string message = reader->read_line();
// 
//         /* Silently skip empty messages */
//         if (!message.empty()) {
//             Nmea_message nmea_msg(message);
// 
//             num_sentences++;
// 
//             if (!nmea_msg.is_nmea()) {
//                 cerr << "Line " << line_no << ": "
//                      << trim(nmea_msg.get_msg_string())
//                      << " (corrupt nmea)" << endl;
// 
//                 valid = false;
//                 num_corrupt++;
// 
//                 if (stop_on_error)
//                     break;
//             } else if (!nmea_msg.valid_checksum()) {
//                 cerr << "Line " << line_no << ": "
//                      << trim(nmea_msg.get_msg_string())
//                      << " (checksum mismatch "
//                      << "'" << nmea_msg.get_checksum() << "' != "
//                      << "'" << nmea_msg.calculate_checksum() << "'"
//                      << ")" << endl;
// 
//                 valid = false;
//                 num_bad_checksum++;
// 
//                 if (stop_on_error)
//                     break;
//             }
//         }
// 
//         line_no++;
// 
//     } while (!reader->done());
// 
//     cout << "Total sentences: " << num_sentences << endl
//          << "Total errors:    " << num_corrupt + num_bad_checksum << endl
//          << "├─ Corrupt:      " << num_corrupt << endl
//          << "└─ Bad Checksum: " << num_bad_checksum << endl
//          << "Error rate:      " << fixed << showpoint << setprecision(2)
//          << (num_sentences == 0 ? 0 :
//          ((double) (num_corrupt + num_bad_checksum)/(double) num_sentences) * 100)
//          << "%" << endl;

    return valid;
}