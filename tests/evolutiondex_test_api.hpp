#pragma once

#include <eosio/chain/abi_serializer.hpp>
#include <eosio/testing/tester.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;

using mvo = fc::mutable_variant_object;
using action_result = base_tester::action_result;

class evolutiondex_test_api {
public:
	name contract;

	evolutiondex_test_api(name acnt, tester* tester) {
		contract = acnt;
		_tester = tester;

		_tester->create_accounts({contract});
		_tester->set_code(contract, contracts::evolutiondex_wasm());
		_tester->set_abi(contract, contracts::evolutiondex_abi().data());

		const auto& accnt = _tester->control->db().get<account_object, by_name>(contract);

		abi_def abi;
		BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
		abi_ser.set_abi(abi, abi_serializer::create_yield_function(fc::microseconds{1000 * 1000}));

		auto auth = authority(1,
							  {key_weight{_tester->get_public_key(contract, "active"), 1}},
							  {permission_level_weight{{contract, config::eosio_code_name}, 1}});

		_tester->set_authority(contract, config::active_name, auth);
	}

	action_result open(name owner, symbol sym, name ram_payer) {
		return push_action(owner, contract, N(open), mvo()("owner", owner)("symbol", sym)("ram_payer", ram_payer));
	}

	action_result openext(name user, name payer, extended_symbol extended_symbol) {
		return push_action(payer, contract, N(openext), mvo()("user", user)("payer", payer)("ext_symbol", extended_symbol));
	}

	action_result closeext(const name user, const name to, const extended_symbol extended_symbol) {
		return push_action(user, contract, N(closeext), mvo()("user", user)("to", to)("ext_symbol", extended_symbol)("memo", ""));
	}

	action_result withdraw(name user, name to, extended_asset to_withdraw) {
		return push_action(user, contract, N(withdraw), mvo()("user", user)("to", to)("to_withdraw", to_withdraw)("memo", ""));
	}

	action_result inittoken(
		name user, symbol new_symbol, extended_asset initial_pool1, extended_asset initial_pool2, int initial_fee, name fee_contract) {
		return push_action(user,
						   contract,
						   N(inittoken),
						   mvo()("user", user)("new_symbol", new_symbol)("initial_pool1", initial_pool1)("initial_pool2", initial_pool2)(
							   "initial_fee", initial_fee)("fee_contract", fee_contract));
	}

	action_result addliquidity(name user, asset to_buy, asset max_asset1, asset max_asset2) {
		return push_action(
			user, contract, N(addliquidity), mvo()("user", user)("to_buy", to_buy)("max_asset1", max_asset1)("max_asset2", max_asset2));
	}

	action_result remliquidity(name user, asset to_sell, asset min_asset1, asset min_asset2) {
		return push_action(
			user, contract, N(remliquidity), mvo()("user", user)("to_sell", to_sell)("min_asset1", min_asset1)("min_asset2", min_asset2));
	}

	action_result exchange(name user, symbol_code pair_token, extended_asset ext_asset_in, asset min_expected) {
		return push_action(user,
						   contract,
						   N(exchange),
						   mvo()("user", user)("pair_token", pair_token)("ext_asset_in", ext_asset_in)("min_expected", min_expected));
	}

	action_result changefee(symbol_code pair_token, int newfee) {
		return push_action(N(wevotethefee), contract, N(changefee), mvo()("pair_token", pair_token)("newfee", newfee));
	}

	fc::variant get_balance(name smartctr, name user, name table, int64_t id, string struc) {
		vector<char> data = _tester->get_row_by_account(smartctr, user, table, name(id));
		return data.empty() ? fc::variant()
							: abi_ser.binary_to_variant(struc, data, abi_serializer::create_yield_function(fc::microseconds{1000 * 1000}));
	}

private:
	action_result push_action(const name& signer, const name& cnt, const action_name& name, const variant_object& data) {
		string action_type_name = abi_ser.get_action_type(name);
		action act;
		act.account = cnt;
		act.name = name;
		act.data = abi_ser.variant_to_binary(action_type_name, data, abi_serializer::create_yield_function(fc::microseconds{1000 * 1000}));

		return _tester->push_action(std::move(act), signer.to_uint64_t());
	}

	abi_serializer abi_ser;
	tester* _tester;
};
