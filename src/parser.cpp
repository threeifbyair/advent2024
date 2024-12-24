module;
#include <boost/parser/parser.hpp>
export module parser;
namespace boost::parser {
    export using boost::parser::parse;
    export using boost::parser::prefix_parse;
    export using boost::parser::int_;
    export using boost::parser::char_;
    export using boost::parser::double_;
    export using boost::parser::float_;
    export using boost::parser::ulong_;
    export using boost::parser::ws;
    export using boost::parser::lit;
    export using boost::parser::string;
    export using boost::parser::tuple;
    export using boost::parser::upper;
    export using boost::parser::lower;
}
