/* Custom manipulators.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>

//{ endm manipulator
const struct endm_creator {
    friend std::ostream& operator<<(std::ostream& os, endm_creator)
    {
        os << "[eol]\n";
        return os;
    }
} endm;

//}

//{ squares manipulator
struct squares_proxy {
public:
    squares_proxy(std::ostream& os) :str(os) {}
    std::ostream& str;
};

const struct squares_creator { 
    friend squares_proxy operator<<(std::ostream& os, squares_creator) {
        return squares_proxy(os);
    }
} squares;

template<typename T>
std::ostream& operator<<(squares_proxy const& q, T const& word) {
    return q.str << "[" << word << "]";
}
//}

//{ add manipulator
struct add_proxy {
    struct add_proxy_next {
        add_proxy_next(std::ostream& os, double const& num) : str(os), previous_num(num) {}
        std::ostream& operator<<(double const& current_num) {
            return str << previous_num + current_num;
        }
        add_proxy_next(std::ostream& os, std::string const& string) : str(os), previous_string(string) {}
        std::ostream& operator<<(std::string const& current_string) {
            return str << previous_string + current_string;
        }
    private:
        std::ostream& str;
        double previous_num;
        std::string previous_string;
    };

    add_proxy(std::ostream& os) : str(os) {}
    struct add_proxy_next operator<<(double const& current_num) {
        return add_proxy_next(str, current_num);
    }

    struct add_proxy_next operator<<(std::string const& current_string) {
        return add_proxy_next(str, current_string);
    }
private:
    std::ostream& str;
};
const struct add_creator { 
    friend add_proxy operator<<(std::ostream& os, add_creator) {
        return add_proxy(os);
    }
} add;
//}

#endif // __IOMANIP_HPP__
