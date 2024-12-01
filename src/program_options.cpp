module;
#include <boost/program_options.hpp>
export module program_options;
namespace boost::program_options {
    export using boost::program_options::options_description;
    export using boost::program_options::value;
    export using boost::program_options::variables_map;
    export using boost::program_options::bool_switch;
    export using boost::program_options::command_line_parser;
    export using boost::program_options::notify;
    export using boost::program_options::parse_command_line;
    export using boost::program_options::store;
}
