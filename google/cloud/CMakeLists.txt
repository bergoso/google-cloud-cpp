# ~~~
# Copyright 2018 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ~~~

# Generate the version information from the CMake values.
configure_file(internal/version_info.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/internal/version_info.h)

set(DOXYGEN_PROJECT_NAME "Google Cloud C++ Client")
set(DOXYGEN_PROJECT_BRIEF "C++ Client Library for Google Cloud Platform")
set(DOXYGEN_PROJECT_NUMBER "${PROJECT_VERSION}")
set(DOXYGEN_EXCLUDE_SYMBOLS "internal" "testing_util" "examples")

# Creates the proto headers needed by doxygen.
set(GOOGLE_CLOUD_CPP_DOXYGEN_DEPS google-cloud-cpp::rpc_status_protos
                                  google-cloud-cpp::bigtable_protos)

include(GoogleCloudCppCommon)

# Define a CMake configuration option to set the build metadata. By default this
# is not initialized.
set(GOOGLE_CLOUD_CPP_BUILD_METADATA
    ""
    CACHE STRING "Append build metadata to the library version number")
# This option is rarely needed. Mark it as "advanced" to remove it from the
# default CMake UIs.
mark_as_advanced(GOOGLE_CLOUD_CPP_BUILD_METADATA)

# Create the file that captures build information. Having access to the compiler
# and build flags at runtime allows us to print better benchmark results.
string(TOUPPER "${CMAKE_BUILD_TYPE}" GOOGLE_CLOUD_CPP_BUILD_TYPE_UPPER)
configure_file(internal/build_info.cc.in internal/build_info.cc)

# the client library
add_library(
    google_cloud_cpp_common # cmake-format: sort
    ${CMAKE_CURRENT_BINARY_DIR}/internal/build_info.cc
    backoff_policy.h
    common_options.h
    credentials.cc
    credentials.h
    future.h
    future_generic.h
    future_void.h
    iam_binding.h
    iam_bindings.cc
    iam_bindings.h
    iam_policy.cc
    iam_policy.h
    idempotency.h
    internal/absl_str_cat_quiet.h
    internal/absl_str_join_quiet.h
    internal/absl_str_replace_quiet.h
    internal/algorithm.h
    internal/api_client_header.cc
    internal/api_client_header.h
    internal/attributes.h
    internal/backoff_policy.cc
    internal/backoff_policy.h
    internal/base64_transforms.cc
    internal/base64_transforms.h
    internal/big_endian.h
    internal/build_info.h
    internal/compiler_info.cc
    internal/compiler_info.h
    internal/compute_engine_util.cc
    internal/compute_engine_util.h
    internal/credentials_impl.cc
    internal/credentials_impl.h
    internal/diagnostics_pop.inc
    internal/diagnostics_push.inc
    internal/disable_deprecation_warnings.inc
    internal/disable_msvc_crt_secure_warnings.inc
    internal/filesystem.cc
    internal/filesystem.h
    internal/format_time_point.cc
    internal/format_time_point.h
    internal/future_base.h
    internal/future_fwd.h
    internal/future_impl.cc
    internal/future_impl.h
    internal/future_then_impl.h
    internal/future_then_meta.h
    internal/getenv.cc
    internal/getenv.h
    internal/invoke_result.h
    internal/ios_flags_saver.h
    internal/log_impl.cc
    internal/log_impl.h
    internal/non_constructible.h
    internal/pagination_range.h
    internal/parse_rfc3339.cc
    internal/parse_rfc3339.h
    internal/populate_common_options.cc
    internal/populate_common_options.h
    internal/port_platform.h
    internal/random.cc
    internal/random.h
    internal/retry_policy.cc
    internal/retry_policy.h
    internal/setenv.cc
    internal/setenv.h
    internal/status_payload_keys.cc
    internal/status_payload_keys.h
    internal/strerror.cc
    internal/strerror.h
    internal/throw_delegate.cc
    internal/throw_delegate.h
    internal/tuple.h
    internal/type_list.h
    internal/user_agent_prefix.cc
    internal/user_agent_prefix.h
    internal/utility.h
    internal/version_info.h
    kms_key_name.cc
    kms_key_name.h
    log.cc
    log.h
    optional.h
    options.cc
    options.h
    polling_policy.h
    project.cc
    project.h
    status.cc
    status.h
    status_or.h
    stream_range.h
    terminate_handler.cc
    terminate_handler.h
    tracing_options.cc
    tracing_options.h
    version.cc
    version.h)
target_link_libraries(
    google_cloud_cpp_common PUBLIC absl::memory absl::optional absl::time
                                   absl::variant Threads::Threads)
google_cloud_cpp_add_common_options(google_cloud_cpp_common)
target_include_directories(
    google_cloud_cpp_common PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                                   $<INSTALL_INTERFACE:include>)

# We're putting generated code into ${PROJECT_BINARY_DIR} (e.g. compiled
# protobufs or build info), so we need it on the include path, however we don't
# want it checked by linters so we mark it as SYSTEM.
target_include_directories(google_cloud_cpp_common SYSTEM
                           PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>)
target_compile_options(google_cloud_cpp_common
                       PUBLIC ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})

set_target_properties(
    google_cloud_cpp_common
    PROPERTIES EXPORT_NAME "google-cloud-cpp::common"
               VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
add_library(google-cloud-cpp::common ALIAS google_cloud_cpp_common)

include(CreateBazelConfig)
create_bazel_config(google_cloud_cpp_common YEAR 2018)

add_subdirectory(testing_util)

# Define the benchmarks in a function so we have a new scope for variable names.
function (google_cloud_cpp_common_define_benchmarks)
    find_package(benchmark CONFIG REQUIRED)

    set(google_cloud_cpp_common_benchmarks # cmake-format: sort
    )

    # Export the list of benchmarks to a .bzl file so we do not need to maintain
    # the list in two places.
    export_list_to_bazel("google_cloud_cpp_common_benchmarks.bzl"
                         "google_cloud_cpp_common_benchmarks" YEAR "2020")

    # Create a custom target so we can say "build all the benchmarks"
    add_custom_target(google-cloud-cpp-common-benchmarks)

    # Generate a target for each benchmark.
    foreach (fname ${google_cloud_cpp_common_benchmarks})
        google_cloud_cpp_add_executable(target "common" "${fname}")
        add_test(NAME ${target} COMMAND ${target})
        target_link_libraries(${target} PRIVATE google-cloud-cpp::common
                                                benchmark::benchmark_main)
        google_cloud_cpp_add_common_options(${target})

        add_dependencies(google-cloud-cpp-common-benchmarks ${target})
    endforeach ()
endfunction ()

if (BUILD_TESTING)
    google_cloud_cpp_common_define_benchmarks()
    set(google_cloud_cpp_common_unit_tests
        # cmake-format: sort
        common_options_test.cc
        future_generic_test.cc
        future_generic_then_test.cc
        future_void_test.cc
        future_void_then_test.cc
        iam_bindings_test.cc
        internal/algorithm_test.cc
        internal/api_client_header_test.cc
        internal/backoff_policy_test.cc
        internal/base64_transforms_test.cc
        internal/big_endian_test.cc
        internal/compiler_info_test.cc
        internal/compute_engine_util_test.cc
        internal/credentials_impl_test.cc
        internal/env_test.cc
        internal/filesystem_test.cc
        internal/format_time_point_test.cc
        internal/future_impl_test.cc
        internal/invoke_result_test.cc
        internal/log_impl_test.cc
        internal/pagination_range_test.cc
        internal/parse_rfc3339_test.cc
        internal/populate_common_options_test.cc
        internal/random_test.cc
        internal/retry_policy_test.cc
        internal/status_payload_keys_test.cc
        internal/strerror_test.cc
        internal/throw_delegate_test.cc
        internal/tuple_test.cc
        internal/type_list_test.cc
        internal/user_agent_prefix_test.cc
        internal/utility_test.cc
        kms_key_name_test.cc
        log_test.cc
        options_test.cc
        polling_policy_test.cc
        project_test.cc
        status_or_test.cc
        status_test.cc
        stream_range_test.cc
        terminate_handler_test.cc
        tracing_options_test.cc)

    # Export the list of unit tests so the Bazel BUILD file can pick it up.
    export_list_to_bazel("google_cloud_cpp_common_unit_tests.bzl"
                         "google_cloud_cpp_common_unit_tests" YEAR "2018")

    foreach (fname ${google_cloud_cpp_common_unit_tests})
        google_cloud_cpp_add_executable(target "common" "${fname}")
        target_link_libraries(
            ${target}
            PRIVATE google_cloud_cpp_testing google-cloud-cpp::common
                    absl::variant GTest::gmock_main GTest::gmock GTest::gtest)
        google_cloud_cpp_add_common_options(${target})
        if (MSVC)
            target_compile_options(${target} PRIVATE "/bigobj")
        endif ()
        add_test(NAME ${target} COMMAND ${target})
    endforeach ()
endif ()

# Export the CMake targets to make it easy to create configuration files.
install(
    EXPORT google_cloud_cpp_common-targets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_common"
    COMPONENT google_cloud_cpp_development)

# Install the libraries and headers in the locations determined by
# GNUInstallDirs
install(
    TARGETS google_cloud_cpp_common
    EXPORT google_cloud_cpp_common-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT google_cloud_cpp_runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_runtime
            NAMELINK_SKIP
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_development)
# With CMake-3.12 and higher we could avoid this separate command (and the
# duplication).
install(
    TARGETS google_cloud_cpp_common
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_development
            NAMELINK_ONLY
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_development)

google_cloud_cpp_install_headers(google_cloud_cpp_common include/google/cloud)

# Setup global variables used in the following *.in files.
set(GOOGLE_CLOUD_CPP_PC_NAME
    "Google Cloud C++ Client Library Common Components")
set(GOOGLE_CLOUD_CPP_PC_DESCRIPTION
    "Common Components used by the Google Cloud C++ Client Libraries.")
set(GOOGLE_CLOUD_CPP_PC_LIBS "-lgoogle_cloud_cpp_common")
string(CONCAT GOOGLE_CLOUD_CPP_PC_REQUIRES "absl_memory" " absl_optional"
              " absl_time")

# Create and install the pkg-config files.
configure_file("${PROJECT_SOURCE_DIR}/google/cloud/config.pc.in"
               "google_cloud_cpp_common.pc" @ONLY)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_common.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
    COMPONENT google_cloud_cpp_development)

# Create and install the CMake configuration files.
include(CMakePackageConfigHelpers)
configure_file("config.cmake.in" "google_cloud_cpp_common-config.cmake" @ONLY)
write_basic_package_version_file(
    "google_cloud_cpp_common-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY ExactVersion)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_common-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_common-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_common"
    COMPONENT google_cloud_cpp_development)

if (GOOGLE_CLOUD_CPP_ENABLE_GRPC)
    # the library
    add_library(
        google_cloud_cpp_grpc_utils # cmake-format: sort
        async_operation.h
        async_streaming_read_write_rpc.h
        background_threads.h
        completion_queue.cc
        completion_queue.h
        connection_options.cc
        connection_options.h
        grpc_error_delegate.cc
        grpc_error_delegate.h
        grpc_options.cc
        grpc_options.h
        grpc_utils/async_operation.h
        grpc_utils/completion_queue.h
        grpc_utils/grpc_error_delegate.h
        grpc_utils/version.h
        iam_updater.h
        internal/async_connection_ready.cc
        internal/async_connection_ready.h
        internal/async_long_running_operation.h
        internal/async_polling_loop.cc
        internal/async_polling_loop.h
        internal/async_read_stream_impl.h
        internal/async_read_write_stream_auth.h
        internal/async_read_write_stream_impl.h
        internal/async_read_write_stream_logging.h
        internal/async_retry_loop.h
        internal/async_retry_unary_rpc.h
        internal/async_rpc_details.h
        internal/background_threads_impl.cc
        internal/background_threads_impl.h
        internal/completion_queue_impl.h
        internal/default_completion_queue_impl.cc
        internal/default_completion_queue_impl.h
        internal/extract_long_running_result.cc
        internal/extract_long_running_result.h
        internal/grpc_access_token_authentication.cc
        internal/grpc_access_token_authentication.h
        internal/grpc_async_access_token_cache.cc
        internal/grpc_async_access_token_cache.h
        internal/grpc_channel_credentials_authentication.cc
        internal/grpc_channel_credentials_authentication.h
        internal/grpc_impersonate_service_account.cc
        internal/grpc_impersonate_service_account.h
        internal/grpc_service_account_authentication.cc
        internal/grpc_service_account_authentication.h
        internal/log_wrapper.cc
        internal/log_wrapper.h
        internal/minimal_iam_credentials_stub.cc
        internal/minimal_iam_credentials_stub.h
        internal/populate_grpc_options.cc
        internal/populate_grpc_options.h
        internal/resumable_streaming_read_rpc.h
        internal/retry_loop.h
        internal/retry_loop_helpers.cc
        internal/retry_loop_helpers.h
        internal/setup_context.h
        internal/streaming_read_rpc.cc
        internal/streaming_read_rpc.h
        internal/streaming_read_rpc_logging.cc
        internal/streaming_read_rpc_logging.h
        internal/streaming_write_rpc.cc
        internal/streaming_write_rpc.h
        internal/streaming_write_rpc_logging.h
        internal/time_utils.cc
        internal/time_utils.h
        internal/unified_grpc_credentials.cc
        internal/unified_grpc_credentials.h)
    target_link_libraries(
        google_cloud_cpp_grpc_utils
        PUBLIC absl::function_ref
               absl::memory
               absl::time
               absl::variant
               google-cloud-cpp::iam_protos
               google-cloud-cpp::longrunning_operations_protos
               google-cloud-cpp::rpc_error_details_protos
               google-cloud-cpp::rpc_status_protos
               google-cloud-cpp::common
               gRPC::grpc++
               gRPC::grpc)
    google_cloud_cpp_add_common_options(google_cloud_cpp_grpc_utils)
    target_include_directories(
        google_cloud_cpp_grpc_utils
        PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
               $<INSTALL_INTERFACE:include>)
    target_compile_options(google_cloud_cpp_grpc_utils
                           PUBLIC ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})
    set_target_properties(
        google_cloud_cpp_grpc_utils
        PROPERTIES EXPORT_NAME "google-cloud-cpp::grpc_utils"
                   VERSION ${PROJECT_VERSION} SOVERSION
                                              ${PROJECT_VERSION_MAJOR})
    add_library(google-cloud-cpp::grpc_utils ALIAS google_cloud_cpp_grpc_utils)

    include(CreateBazelConfig)
    create_bazel_config(google_cloud_cpp_grpc_utils YEAR 2019)

    # Define the benchmarks in a function so we have a new scope for variable
    # names.
    function (google_cloud_cpp_grpc_utils_define_benchmarks)
        find_package(benchmark CONFIG REQUIRED)

        set(google_cloud_cpp_grpc_utils_benchmarks
            # cmake-format: sortable
            completion_queue_benchmark.cc)

        # Export the list of benchmarks to a .bzl file so we do not need to
        # maintain the list in two places.
        export_list_to_bazel(
            "google_cloud_cpp_grpc_utils_benchmarks.bzl"
            "google_cloud_cpp_grpc_utils_benchmarks" YEAR "2020")

        # Create a custom target so we can say "build all the benchmarks"
        add_custom_target(google-cloud-cpp-grpc-utils-benchmarks)

        # Generate a target for each benchmark.
        foreach (fname ${google_cloud_cpp_grpc_utils_benchmarks})
            google_cloud_cpp_add_executable(target "common" "${fname}")
            add_test(NAME ${target} COMMAND ${target})
            target_link_libraries(
                ${target}
                PRIVATE google-cloud-cpp::grpc_utils google-cloud-cpp::common
                        benchmark::benchmark_main)
            google_cloud_cpp_add_common_options(${target})

            add_dependencies(google-cloud-cpp-grpc-utils-benchmarks ${target})
        endforeach ()
    endfunction ()

    function (google_cloud_cpp_grpc_utils_add_test fname labels)
        google_cloud_cpp_add_executable(target "common_grpc_utils" "${fname}")
        target_link_libraries(
            ${target}
            PRIVATE google-cloud-cpp::grpc_utils
                    google_cloud_cpp_testing_grpc
                    google_cloud_cpp_testing
                    google-cloud-cpp::common
                    google-cloud-cpp::iam_protos
                    google-cloud-cpp::bigtable_protos
                    google-cloud-cpp::spanner_protos
                    absl::variant
                    GTest::gmock_main
                    GTest::gmock
                    GTest::gtest
                    gRPC::grpc++
                    gRPC::grpc)
        google_cloud_cpp_add_common_options(${target})
        if (MSVC)
            target_compile_options(${target} PRIVATE "/bigobj")
        endif ()
        add_test(NAME ${target} COMMAND ${target})
        set_tests_properties(${target} PROPERTIES LABELS "${labels}")
    endfunction ()

    if (BUILD_TESTING)
        google_cloud_cpp_grpc_utils_define_benchmarks()

        # List the unit tests, then setup the targets and dependencies.
        set(google_cloud_cpp_grpc_utils_unit_tests
            # cmake-format: sort
            completion_queue_test.cc
            connection_options_test.cc
            grpc_error_delegate_test.cc
            grpc_options_test.cc
            internal/async_connection_ready_test.cc
            internal/async_long_running_operation_test.cc
            internal/async_polling_loop_test.cc
            internal/async_read_write_stream_auth_test.cc
            internal/async_read_write_stream_impl_test.cc
            internal/async_read_write_stream_logging_test.cc
            internal/async_retry_loop_test.cc
            internal/async_retry_unary_rpc_test.cc
            internal/background_threads_impl_test.cc
            internal/extract_long_running_result_test.cc
            internal/grpc_access_token_authentication_test.cc
            internal/grpc_async_access_token_cache_test.cc
            internal/grpc_channel_credentials_authentication_test.cc
            internal/grpc_service_account_authentication_test.cc
            internal/log_wrapper_test.cc
            internal/minimal_iam_credentials_stub_test.cc
            internal/populate_grpc_options_test.cc
            internal/resumable_streaming_read_rpc_test.cc
            internal/retry_loop_test.cc
            internal/streaming_read_rpc_logging_test.cc
            internal/streaming_read_rpc_test.cc
            internal/streaming_write_rpc_logging_test.cc
            internal/streaming_write_rpc_test.cc
            internal/time_utils_test.cc
            internal/unified_grpc_credentials_test.cc)

        # List the unit tests, then setup the targets and dependencies.
        set(google_cloud_cpp_grpc_utils_integration_tests
            # cmake-format: sort
            internal/grpc_impersonate_service_account_integration_test.cc)

        # Export the list of unit and integration tests so the Bazel BUILD file
        # can pick them up.
        export_list_to_bazel(
            "google_cloud_cpp_grpc_utils_unit_tests.bzl"
            "google_cloud_cpp_grpc_utils_unit_tests" YEAR "2019")
        export_list_to_bazel(
            "google_cloud_cpp_grpc_utils_integration_tests.bzl"
            "google_cloud_cpp_grpc_utils_integration_tests" YEAR "2021")

        foreach (fname ${google_cloud_cpp_grpc_utils_unit_tests})
            google_cloud_cpp_grpc_utils_add_test("${fname}" "")
        endforeach ()

        foreach (fname ${google_cloud_cpp_grpc_utils_integration_tests})
            google_cloud_cpp_grpc_utils_add_test("${fname}"
                                                 "integration-test-production")
        endforeach ()
    endif ()

    # Install the libraries and headers in the locations determined by
    # GNUInstallDirs
    install(
        TARGETS
        EXPORT grpc_utils-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development)

    # Export the CMake targets to make it easy to create configuration files.
    install(
        EXPORT grpc_utils-targets
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_grpc_utils"
        COMPONENT google_cloud_cpp_development)

    install(
        TARGETS google_cloud_cpp_grpc_utils
        EXPORT grpc_utils-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT google_cloud_cpp_runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_runtime
                NAMELINK_SKIP
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development)
    # With CMake-3.12 and higher we could avoid this separate command (and the
    # duplication).
    install(
        TARGETS google_cloud_cpp_grpc_utils
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development
                NAMELINK_ONLY
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development)

    google_cloud_cpp_install_headers(google_cloud_cpp_grpc_utils
                                     include/google/cloud)

    # Setup global variables used in the following *.in files.
    set(GOOGLE_CLOUD_CPP_PC_NAME
        "gRPC Utilities for the Google Cloud C++ Client Library")
    set(GOOGLE_CLOUD_CPP_PC_DESCRIPTION
        "Provides gRPC Utilities for the Google Cloud C++ Client Library.")
    string(
        CONCAT GOOGLE_CLOUD_CPP_PC_REQUIRES
               "google_cloud_cpp_common"
               " google_cloud_cpp_iam_protos"
               " google_cloud_cpp_longrunning_operations_protos"
               " google_cloud_cpp_rpc_status_protos")
    string(CONCAT GOOGLE_CLOUD_CPP_PC_LIBS "-lgoogle_cloud_cpp_grpc_utils")

    # Create and install the pkg-config files.
    configure_file("${PROJECT_SOURCE_DIR}/google/cloud/config.pc.in"
                   "google_cloud_cpp_grpc_utils.pc" @ONLY)
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_grpc_utils.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
        COMPONENT google_cloud_cpp_development)

    # Create and install the CMake configuration files.
    configure_file("grpc_utils/config.cmake.in"
                   "google_cloud_cpp_grpc_utils-config.cmake" @ONLY)
    write_basic_package_version_file(
        "google_cloud_cpp_grpc_utils-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY ExactVersion)

    install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_grpc_utils-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_grpc_utils-config-version.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_grpc_utils"
        COMPONENT google_cloud_cpp_development)
endif ()

if (GOOGLE_CLOUD_CPP_ENABLE_REST)
    include(IncludeNlohmannJson)
    include(FindCurlWithTargets)
    find_package(OpenSSL REQUIRED)

    # the library
    add_library(
        google_cloud_cpp_rest_internal # cmake-format: sort
        internal/binary_data_as_debug_string.cc
        internal/binary_data_as_debug_string.h
        internal/curl_handle.cc
        internal/curl_handle.h
        internal/curl_handle_factory.cc
        internal/curl_handle_factory.h
        internal/curl_impl.cc
        internal/curl_impl.h
        internal/curl_options.h
        internal/curl_wrappers.cc
        internal/curl_wrappers.h
        internal/http_payload.cc
        internal/http_payload.h
        internal/make_jwt_assertion.cc
        internal/make_jwt_assertion.h
        internal/oauth2_access_token_credentials.cc
        internal/oauth2_access_token_credentials.h
        internal/oauth2_anonymous_credentials.cc
        internal/oauth2_anonymous_credentials.h
        internal/oauth2_authorized_user_credentials.cc
        internal/oauth2_authorized_user_credentials.h
        internal/oauth2_compute_engine_credentials.cc
        internal/oauth2_compute_engine_credentials.h
        internal/oauth2_credential_constants.h
        internal/oauth2_credentials.cc
        internal/oauth2_credentials.h
        internal/oauth2_error_credentials.cc
        internal/oauth2_error_credentials.h
        internal/oauth2_google_application_default_credentials_file.cc
        internal/oauth2_google_application_default_credentials_file.h
        internal/oauth2_google_credentials.cc
        internal/oauth2_google_credentials.h
        internal/oauth2_impersonate_service_account_credentials.cc
        internal/oauth2_impersonate_service_account_credentials.h
        internal/oauth2_minimal_iam_credentials_rest.cc
        internal/oauth2_minimal_iam_credentials_rest.h
        internal/oauth2_refreshing_credentials_wrapper.cc
        internal/oauth2_refreshing_credentials_wrapper.h
        internal/oauth2_service_account_credentials.cc
        internal/oauth2_service_account_credentials.h
        internal/openssl_util.cc
        internal/openssl_util.h
        internal/rest_client.cc
        internal/rest_client.h
        internal/rest_options.h
        internal/rest_request.cc
        internal/rest_request.h
        internal/rest_response.cc
        internal/rest_response.h
        internal/unified_rest_credentials.cc
        internal/unified_rest_credentials.h)
    target_link_libraries(
        google_cloud_cpp_rest_internal
        PUBLIC absl::span google-cloud-cpp::common CURL::libcurl
               nlohmann_json::nlohmann_json OpenSSL::SSL OpenSSL::Crypto)
    google_cloud_cpp_add_common_options(google_cloud_cpp_rest_internal)
    target_include_directories(
        google_cloud_cpp_rest_internal
        PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
               $<INSTALL_INTERFACE:include>)
    target_compile_options(google_cloud_cpp_rest_internal
                           PUBLIC ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})
    set_target_properties(
        google_cloud_cpp_rest_internal
        PROPERTIES EXPORT_NAME "google-cloud-cpp::rest-internal"
                   VERSION ${PROJECT_VERSION} SOVERSION
                                              ${PROJECT_VERSION_MAJOR})
    add_library(google-cloud-cpp::rest-internal ALIAS
                google_cloud_cpp_rest_internal)

    include(CreateBazelConfig)
    create_bazel_config(google_cloud_cpp_rest_internal YEAR 2021)

    # Define the unit tests in a function so we have a new scope for variable
    # names.
    function (google_cloud_cpp_rest_internal_add_test fname labels)
        google_cloud_cpp_add_executable(target "rest_internal" "${fname}")
        target_link_libraries(
            ${target}
            PRIVATE google-cloud-cpp::rest-internal
                    google_cloud_cpp_testing
                    google_cloud_cpp_testing_rest
                    google-cloud-cpp::common
                    absl::span
                    GTest::gmock_main
                    GTest::gmock
                    GTest::gtest
                    CURL::libcurl)
        google_cloud_cpp_add_common_options(${target})
        if (MSVC)
            target_compile_options(${target} PRIVATE "/bigobj")
        endif ()
        add_test(NAME ${target} COMMAND ${target})
        set_tests_properties(${target} PROPERTIES LABELS "${labels}")
    endfunction ()

    if (BUILD_TESTING)
        # List the unit tests, then setup the targets and dependencies.
        set(google_cloud_cpp_rest_internal_unit_tests
            # cmake-format: sort
            internal/binary_data_as_debug_string_test.cc
            internal/curl_handle_factory_test.cc
            internal/curl_handle_test.cc
            internal/curl_impl_test.cc
            internal/curl_wrappers_test.cc
            internal/http_payload_test.cc
            internal/make_jwt_assertion_test.cc
            internal/oauth2_access_token_credentials_test.cc
            internal/oauth2_anonymous_credentials_test.cc
            internal/oauth2_authorized_user_credentials_test.cc
            internal/oauth2_compute_engine_credentials_test.cc
            internal/oauth2_google_application_default_credentials_file_test.cc
            internal/oauth2_google_credentials_test.cc
            internal/oauth2_impersonate_service_account_credentials_test.cc
            internal/oauth2_minimal_iam_credentials_rest_test.cc
            internal/oauth2_refreshing_credentials_wrapper_test.cc
            internal/oauth2_service_account_credentials_test.cc
            internal/openssl_util_test.cc
            internal/rest_client_test.cc
            internal/rest_request_test.cc
            internal/rest_response_test.cc
            internal/unified_rest_credentials_test.cc)

        # List the emulator integration tests, then setup the targets and
        # dependencies.
        set(google_cloud_cpp_rest_internal_emulator_integration_tests
            # cmake-format: sort
            internal/rest_client_integration_test.cc)

        # List the production integration tests, then setup the targets and
        # dependencies.
        set(google_cloud_cpp_rest_internal_production_integration_tests
            # cmake-format: sort
            internal/unified_rest_credentials_integration_test.cc)

        # Export the list of unit and integration tests so the Bazel BUILD file
        # can pick them up.
        export_list_to_bazel(
            "google_cloud_cpp_rest_internal_unit_tests.bzl"
            "google_cloud_cpp_rest_internal_unit_tests" YEAR 2021)
        export_list_to_bazel(
            "google_cloud_cpp_rest_internal_emulator_integration_tests.bzl"
            "google_cloud_cpp_rest_internal_emulator_integration_tests" YEAR
            2022)
        export_list_to_bazel(
            "google_cloud_cpp_rest_internal_production_integration_tests.bzl"
            "google_cloud_cpp_rest_internal_production_integration_tests" YEAR
            2022)

        foreach (fname ${google_cloud_cpp_rest_internal_unit_tests})
            google_cloud_cpp_rest_internal_add_test("${fname}" "")
        endforeach ()

        foreach (fname
                 ${google_cloud_cpp_rest_internal_emulator_integration_tests})
            google_cloud_cpp_rest_internal_add_test(
                "${fname}" "integration-test;integration-test-emulator")
        endforeach ()

        foreach (fname
                 ${google_cloud_cpp_rest_internal_production_integration_tests})
            google_cloud_cpp_rest_internal_add_test(
                "${fname}" "integration-test;integration-test-production")
        endforeach ()
    endif ()

    # Install the libraries and headers in the locations determined by
    # GNUInstallDirs
    install(
        TARGETS
        EXPORT rest-internal-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development)

    # Export the CMake targets to make it easy to create configuration files.
    install(
        EXPORT rest-internal-targets
        DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_rest_internal"
        COMPONENT google_cloud_cpp_development)

    install(
        TARGETS google_cloud_cpp_rest_internal
        EXPORT rest-internal-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT google_cloud_cpp_runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_runtime
                NAMELINK_SKIP
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development)
    # With CMake-3.12 and higher we could avoid this separate command (and the
    # duplication).
    install(
        TARGETS google_cloud_cpp_rest_internal
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development
                NAMELINK_ONLY
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT google_cloud_cpp_development)

    google_cloud_cpp_install_headers(google_cloud_cpp_rest_internal
                                     include/google/cloud)

    # Setup global variables used in the following *.in files.
    set(GOOGLE_CLOUD_CPP_PC_NAME
        "REST library for the Google Cloud C++ Client Library")
    set(GOOGLE_CLOUD_CPP_PC_DESCRIPTION
        "Provides REST Transport for the Google Cloud C++ Client Library.")
    string(CONCAT GOOGLE_CLOUD_CPP_PC_REQUIRES "google_cloud_cpp_common")
    string(CONCAT GOOGLE_CLOUD_CPP_PC_LIBS "-lgoogle_cloud_cpp_rest_internal")

    # Create and install the pkg-config files.
    configure_file("${PROJECT_SOURCE_DIR}/google/cloud/config.pc.in"
                   "google_cloud_cpp_rest_internal.pc" @ONLY)
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_rest_internal.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
        COMPONENT google_cloud_cpp_development)

    # Create and install the CMake configuration files.
    configure_file("grpc_utils/config.cmake.in"
                   "google_cloud_cpp_rest_internal-config.cmake" @ONLY)
    write_basic_package_version_file(
        "google_cloud_cpp_rest_internal-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY ExactVersion)

    install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_rest_internal-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_rest_internal-config-version.cmake"
        DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_rest_internal"
        COMPONENT google_cloud_cpp_development)
endif ()
