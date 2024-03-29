#pragma once

#define SYMBOLS \
X(napi_get_last_error_info) \
X(napi_get_undefined) \
X(napi_get_null) \
X(napi_get_global) \
X(napi_get_boolean) \
X(napi_create_object) \
X(napi_create_array) \
X(napi_create_array_with_length) \
X(napi_create_double) \
X(napi_create_int32) \
X(napi_create_uint32) \
X(napi_create_int64) \
X(napi_create_string_latin1) \
X(napi_create_string_utf8) \
X(napi_create_string_utf16) \
X(napi_create_symbol) \
X(napi_create_function) \
X(napi_create_error) \
X(napi_create_type_error) \
X(napi_create_range_error) \
X(napi_typeof) \
X(napi_get_value_double) \
X(napi_get_value_int32) \
X(napi_get_value_uint32) \
X(napi_get_value_int64) \
X(napi_get_value_bool) \
X(napi_get_value_string_latin1) \
X(napi_get_value_string_utf8) \
X(napi_get_value_string_utf16) \
X(napi_coerce_to_bool) \
X(napi_coerce_to_number) \
X(napi_coerce_to_object) \
X(napi_coerce_to_string) \
X(napi_get_prototype) \
X(napi_get_property_names) \
X(napi_set_property) \
X(napi_has_property) \
X(napi_get_property) \
X(napi_delete_property) \
X(napi_has_own_property) \
X(napi_set_named_property) \
X(napi_has_named_property) \
X(napi_get_named_property) \
X(napi_set_element) \
X(napi_has_element) \
X(napi_get_element) \
X(napi_delete_element) \
X(napi_define_properties) \
X(napi_is_array) \
X(napi_get_array_length) \
X(napi_strict_equals) \
X(napi_call_function) \
X(napi_new_instance) \
X(napi_instanceof) \
X(napi_get_cb_info) \
X(napi_get_new_target) \
X(napi_define_class) \
X(napi_wrap) \
X(napi_unwrap) \
X(napi_remove_wrap) \
X(napi_create_external) \
X(napi_get_value_external) \
X(napi_create_reference) \
X(napi_delete_reference) \
X(napi_reference_ref) \
X(napi_reference_unref) \
X(napi_get_reference_value) \
X(napi_open_handle_scope) \
X(napi_close_handle_scope) \
X(napi_open_escapable_handle_scope) \
X(napi_close_escapable_handle_scope) \
X(napi_escape_handle) \
X(napi_throw) \
X(napi_throw_error) \
X(napi_throw_type_error) \
X(napi_throw_range_error) \
X(napi_is_error) \
X(napi_is_exception_pending) \
X(napi_get_and_clear_last_exception) \
X(napi_is_arraybuffer) \
X(napi_create_arraybuffer) \
X(napi_create_external_arraybuffer) \
X(napi_get_arraybuffer_info) \
X(napi_is_typedarray) \
X(napi_create_typedarray) \
X(napi_get_typedarray_info) \
X(napi_create_dataview) \
X(napi_is_dataview) \
X(napi_get_dataview_info) \
X(napi_get_version) \
X(napi_create_promise) \
X(napi_resolve_deferred) \
X(napi_reject_deferred) \
X(napi_is_promise) \
X(napi_run_script) \
X(napi_adjust_external_memory) \
X(napi_create_date) \
X(napi_is_date) \
X(napi_get_date_value) \
X(napi_add_finalizer) \
X(napi_create_bigint_int64) \
X(napi_create_bigint_uint64) \
X(napi_create_bigint_words) \
X(napi_get_value_bigint_int64) \
X(napi_get_value_bigint_uint64) \
X(napi_get_value_bigint_words) \
X(napi_get_all_property_names) \
X(napi_set_instance_data) \
X(napi_get_instance_data) \
X(napi_detach_arraybuffer) \
X(napi_is_detached_arraybuffer) \
X(napi_type_tag_object) \
X(napi_check_object_type_tag) \
X(napi_object_freeze) \
X(napi_object_seal) \
X(napi_module_register) \
X(napi_async_init) \
X(napi_async_destroy) \
X(napi_make_callback) \
X(napi_create_buffer) \
X(napi_create_external_buffer) \
X(napi_create_buffer_copy) \
X(napi_is_buffer) \
X(napi_get_buffer_info) \
X(napi_create_async_work) \
X(napi_delete_async_work) \
X(napi_queue_async_work) \
X(napi_cancel_async_work) \
X(napi_get_node_version) \
X(napi_get_uv_event_loop) \
X(napi_fatal_exception) \
X(napi_add_env_cleanup_hook) \
X(napi_remove_env_cleanup_hook) \
X(napi_open_callback_scope) \
X(napi_close_callback_scope) \
X(napi_create_threadsafe_function) \
X(napi_get_threadsafe_function_context) \
X(napi_call_threadsafe_function) \
X(napi_acquire_threadsafe_function) \
X(napi_release_threadsafe_function) \
X(napi_unref_threadsafe_function) \
X(napi_ref_threadsafe_function) \
X(napi_add_async_cleanup_hook) \
X(napi_remove_async_cleanup_hook)
