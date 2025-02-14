// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/networkmanagement/v1/reachability.proto

#include "google/cloud/networkmanagement/internal/reachability_connection_impl.h"
#include "google/cloud/networkmanagement/internal/reachability_option_defaults.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/async_long_running_operation.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/retry_loop.h"
#include <memory>

namespace google {
namespace cloud {
namespace networkmanagement_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ReachabilityServiceConnectionImpl::ReachabilityServiceConnectionImpl(
    std::unique_ptr<google::cloud::BackgroundThreads> background,
    std::shared_ptr<networkmanagement_internal::ReachabilityServiceStub> stub,
    Options options)
    : background_(std::move(background)),
      stub_(std::move(stub)),
      options_(internal::MergeOptions(
          std::move(options),
          networkmanagement_internal::ReachabilityServiceDefaultOptions(
              ReachabilityServiceConnection::options()))) {}

StreamRange<google::cloud::networkmanagement::v1::ConnectivityTest>
ReachabilityServiceConnectionImpl::ListConnectivityTests(
    google::cloud::networkmanagement::v1::ListConnectivityTestsRequest
        request) {
  request.clear_page_token();
  auto stub = stub_;
  auto retry =
      std::shared_ptr<networkmanagement::ReachabilityServiceRetryPolicy const>(
          retry_policy());
  auto backoff = std::shared_ptr<BackoffPolicy const>(backoff_policy());
  auto idempotency = idempotency_policy()->ListConnectivityTests(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::cloud::networkmanagement::v1::ConnectivityTest>>(
      std::move(request),
      [stub, retry, backoff, idempotency,
       function_name](google::cloud::networkmanagement::v1::
                          ListConnectivityTestsRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](grpc::ClientContext& context,
                   google::cloud::networkmanagement::v1::
                       ListConnectivityTestsRequest const& request) {
              return stub->ListConnectivityTests(context, request);
            },
            r, function_name);
      },
      [](google::cloud::networkmanagement::v1::ListConnectivityTestsResponse
             r) {
        std::vector<google::cloud::networkmanagement::v1::ConnectivityTest>
            result(r.resources().size());
        auto& messages = *r.mutable_resources();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::cloud::networkmanagement::v1::ConnectivityTest>
ReachabilityServiceConnectionImpl::GetConnectivityTest(
    google::cloud::networkmanagement::v1::GetConnectivityTestRequest const&
        request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->GetConnectivityTest(request),
      [this](grpc::ClientContext& context,
             google::cloud::networkmanagement::v1::
                 GetConnectivityTestRequest const& request) {
        return stub_->GetConnectivityTest(context, request);
      },
      request, __func__);
}

future<StatusOr<google::cloud::networkmanagement::v1::ConnectivityTest>>
ReachabilityServiceConnectionImpl::CreateConnectivityTest(
    google::cloud::networkmanagement::v1::CreateConnectivityTestRequest const&
        request) {
  auto stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::cloud::networkmanagement::v1::ConnectivityTest>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::networkmanagement::v1::
                 CreateConnectivityTestRequest const& request) {
        return stub->AsyncCreateConnectivityTest(cq, std::move(context),
                                                 request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::cloud::networkmanagement::v1::ConnectivityTest>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->CreateConnectivityTest(request), polling_policy(),
      __func__);
}

future<StatusOr<google::cloud::networkmanagement::v1::ConnectivityTest>>
ReachabilityServiceConnectionImpl::UpdateConnectivityTest(
    google::cloud::networkmanagement::v1::UpdateConnectivityTestRequest const&
        request) {
  auto stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::cloud::networkmanagement::v1::ConnectivityTest>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::networkmanagement::v1::
                 UpdateConnectivityTestRequest const& request) {
        return stub->AsyncUpdateConnectivityTest(cq, std::move(context),
                                                 request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::cloud::networkmanagement::v1::ConnectivityTest>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->UpdateConnectivityTest(request), polling_policy(),
      __func__);
}

future<StatusOr<google::cloud::networkmanagement::v1::ConnectivityTest>>
ReachabilityServiceConnectionImpl::RerunConnectivityTest(
    google::cloud::networkmanagement::v1::RerunConnectivityTestRequest const&
        request) {
  auto stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::cloud::networkmanagement::v1::ConnectivityTest>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::networkmanagement::v1::
                 RerunConnectivityTestRequest const& request) {
        return stub->AsyncRerunConnectivityTest(cq, std::move(context),
                                                request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::cloud::networkmanagement::v1::ConnectivityTest>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->RerunConnectivityTest(request), polling_policy(),
      __func__);
}

future<StatusOr<google::cloud::networkmanagement::v1::OperationMetadata>>
ReachabilityServiceConnectionImpl::DeleteConnectivityTest(
    google::cloud::networkmanagement::v1::DeleteConnectivityTestRequest const&
        request) {
  auto stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::cloud::networkmanagement::v1::OperationMetadata>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::networkmanagement::v1::
                 DeleteConnectivityTestRequest const& request) {
        return stub->AsyncDeleteConnectivityTest(cq, std::move(context),
                                                 request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultMetadata<
          google::cloud::networkmanagement::v1::OperationMetadata>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->DeleteConnectivityTest(request), polling_policy(),
      __func__);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace networkmanagement_internal
}  // namespace cloud
}  // namespace google
