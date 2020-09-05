CWD := $(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST))))))

.PHONY: help

help: ## This help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := help

build: ## Build using Docker
	@docker run -t -i -v $(CWD):/dapp orbiterco/eosio -c "export BOOST_ROOT=/root/eosio/1.8/src/boost_1_70_0 && cd /dapp && /bin/bash /dapp/build.sh -y"

build-test: ## Build & Test using Docker
	@docker run -t -i -v $(CWD):/dapp orbiterco/eosio -c "export BOOST_ROOT=/root/eosio/1.8/src/boost_1_70_0 && cd /dapp && /bin/bash /dapp/build.sh -y && /dapp/build/tests/unit_test"

build-local: ## Build local
	./build.sh -y

test-local: ## Test local
	./build/tests/unit_test

build-test-debug: ## Build & Test with debug using Docker
	@docker run -t -i -v $(CWD):/dapp orbiterco/eosio -c "export BOOST_ROOT=/root/eosio/1.8/src/boost_1_70_0 && cd /dapp && /bin/bash /dapp/build.sh -y && /dapp/build/tests/unit_test -- --verbose"