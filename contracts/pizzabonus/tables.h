#pragma once

#include <eosio/eosio.hpp>

struct coupon
{
  uint16_t value;
  bool active = false;
};

// EOSIO_REFLECT(Coupon, value, active);

struct [[eosio::table]] pizza_user
{
  eosio::name username = ""_n;
  uint64_t coupons = 0;
  uint64_t pizzas_bought = 0;

  // /coupon cpn = coupon{};

  // eosio::name primary_key() const { return username; }
  uint64_t primary_key() const { return username.value; }
};

// EOSIO_REFLECT(User, username, cpm);

typedef eosio::multi_index<"user"_n, pizza_user> usertable_t;
