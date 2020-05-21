#include <eosio/eosio.hpp>
#include "./pizzabonus.h"

pizzabonus::pizzabonus(name self_contract, name user, eosio::datastream<const char *> ds)
    : contract(self_contract, user, ds), ut(self_contract, self_contract.value)
{
  coupon_threshold = 5;
}

void pizzabonus::buypizza(name user)
{
  // user exist
  eosio::require_auth(user);
  auto iterator = ut.find(user.value);
  if (iterator == ut.end())
  {
    eosio::print("New user registered:", user);
    ut.emplace(user, [&](auto &row){
      row.username = user;
      row.coupons = 0;
      row.pizzas_bought = 1;
    });
  }
  else
  {
    ut.modify(iterator, user, [&](auto &row){
      row.pizzas_bought++;
     // eosio::print(user, "bought a pizza, counter:", row.pizzas_bought);
      if (row.pizzas_bought == coupon_threshold)
      {
        row.coupons++;
        row.pizzas_bought = 0;
        eosio::print(user, "Won a coupon, counter:", row.coupons);
      }
      eosio::print(user, "Pizzas, counter:", row.pizzas_bought);
    });
  }
}

uint16_t pizzabonus::getcoupons(name user)
{
  //
  return 0;
}

void pizzabonus::redeemcoupon(name user)
{
  //
}

void pizzabonus::chngthrhld(name user, uint16_t newvalue)
{
  //
}
