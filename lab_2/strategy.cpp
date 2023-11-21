#include "strategy.h"

state ge16_plain::make_choice(int sum, int opponents_card){
    return sum >= 16 ? state::stop : state::take_more;
}

state ge18_plain::make_choice(int sum, int opponents_card){
    return sum >= 18 ? state::stop : state::take_more;
}
