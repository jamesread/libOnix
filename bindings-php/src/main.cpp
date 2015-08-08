#include <iostream>
#include "common.hpp"
#include "surface.hpp"

extern "C" {
#include "php.h"

#define PHP_ONIX_VERSION "1.0"
#define PHP_ONIX_EXTNAME "Onix"

PHP_FUNCTION(onix_binding_version) {
	RETURN_STRING(PHP_ONIX_VERSION, 1);
}

PHP_FUNCTION(onix_greeting) {
	RETURN_STRING(greeting(), 1);
}

static zend_function_entry onix_functions[] = {
	PHP_FE(onix_binding_version, NULL) {NULL, NULL, NULL},
	PHP_FE(onix_greeting, NULL) {NULL, NULL, NULL}
};

zend_module_entry onix_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_ONIX_EXTNAME,
	onix_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_ONIX_VERSION,
	STANDARD_MODULE_PROPERTIES
};
}
