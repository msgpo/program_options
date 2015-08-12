/*
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Product name: program_options
  Copyright (C) Wallix 2015
  Author(s): Jonathan Poelen
*/

#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestProgramOptions
#include <boost/test/auto_unit_test.hpp>

#include "program_options.hpp"

namespace po = program_options;

template<class Exception>
bool is_except( Exception const & ) { return true; }

BOOST_AUTO_TEST_CASE(TestProgramOptions)
{
    int i = 0;
    po::options_description desc({
        {'v', "verbose", &i, "verbosity"},
        {'g', "blah blah"},
        {'u', "blah blah"}
    });

    {
        char const * av[] {
            "", "--verbose", "3", "-u"
        };
        auto map = po::parse_command_line(sizeof(av)/sizeof(av[0]), const_cast<char**>(av), desc);

        BOOST_CHECK_EQUAL(map.count("verbose"), 1);
        BOOST_CHECK_EQUAL(map.count('v'), 1);
        BOOST_CHECK_EQUAL(map.count('g'), 0);
        BOOST_CHECK_EQUAL(map.count('u'), 1);
        BOOST_CHECK_EQUAL(i, 3);
    }

    {
        char const * av[] {
            "", "-gv5"
        };
        auto map = po::parse_command_line(sizeof(av)/sizeof(av[0]), const_cast<char**>(av), desc);

        BOOST_CHECK_EQUAL(map.count("verbose"), 1);
        BOOST_CHECK_EQUAL(map.count('v'), 1);
        BOOST_CHECK_EQUAL(map.count('g'), 1);
        BOOST_CHECK_EQUAL(map.count('u'), 0);
        BOOST_CHECK_EQUAL(i, 5);
    }

    {
        char const * av[] {
            "", "-ug"
        };
        auto map = po::parse_command_line(sizeof(av)/sizeof(av[0]), const_cast<char**>(av), desc);

        BOOST_CHECK_EQUAL(map.count("verbose"), 0);
        BOOST_CHECK_EQUAL(map.count('v'), 0);
        BOOST_CHECK_EQUAL(map.count('g'), 1);
        BOOST_CHECK_EQUAL(map.count('u'), 1);
    }

    {
        char const * av[] {
            "", "-v"
        };

        BOOST_CHECK_EXCEPTION(
            po::parse_command_line(sizeof(av)/sizeof(av[0]), const_cast<char**>(av), desc),
            po::invalid_command_line_syntax,
            is_except<po::invalid_command_line_syntax>
        );
    }

    {
        char const * av[] {
            "", "-v22222222222222222222222222222222222222222222222222222222222222222222"
        };

        BOOST_CHECK_EXCEPTION(
            po::parse_command_line(sizeof(av)/sizeof(av[0]), const_cast<char**>(av), desc),
            po::invalid_option_value,
            is_except<po::invalid_option_value>
        );
    }

    {
        char const * av[] {
            "", "-"
        };

        BOOST_CHECK_EXCEPTION(
            po::parse_command_line(sizeof(av)/sizeof(av[0]), const_cast<char**>(av), desc),
            po::unknow_option,
            is_except<po::unknow_option>
        );
    }
}

