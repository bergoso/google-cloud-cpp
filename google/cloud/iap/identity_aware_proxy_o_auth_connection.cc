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
// source: google/cloud/iap/v1/service.proto

#include "google/cloud/iap/identity_aware_proxy_o_auth_connection.h"
#include "google/cloud/iap/identity_aware_proxy_o_auth_options.h"
#include "google/cloud/iap/internal/identity_aware_proxy_o_auth_connection_impl.h"
#include "google/cloud/iap/internal/identity_aware_proxy_o_auth_option_defaults.h"
#include "google/cloud/iap/internal/identity_aware_proxy_o_auth_stub_factory.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include <memory>

namespace google {
namespace cloud {
namespace iap {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

IdentityAwareProxyOAuthServiceConnection::
    ~IdentityAwareProxyOAuthServiceConnection() = default;

StatusOr<google::cloud::iap::v1::ListBrandsResponse>
IdentityAwareProxyOAuthServiceConnection::ListBrands(
    google::cloud::iap::v1::ListBrandsRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::iap::v1::Brand>
IdentityAwareProxyOAuthServiceConnection::CreateBrand(
    google::cloud::iap::v1::CreateBrandRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::iap::v1::Brand>
IdentityAwareProxyOAuthServiceConnection::GetBrand(
    google::cloud::iap::v1::GetBrandRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::iap::v1::IdentityAwareProxyClient>
IdentityAwareProxyOAuthServiceConnection::CreateIdentityAwareProxyClient(
    google::cloud::iap::v1::CreateIdentityAwareProxyClientRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::iap::v1::IdentityAwareProxyClient>
    IdentityAwareProxyOAuthServiceConnection::ListIdentityAwareProxyClients(
        google::cloud::iap::v1::
            ListIdentityAwareProxyClientsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::iap::v1::IdentityAwareProxyClient>>();
}

StatusOr<google::cloud::iap::v1::IdentityAwareProxyClient>
IdentityAwareProxyOAuthServiceConnection::GetIdentityAwareProxyClient(
    google::cloud::iap::v1::GetIdentityAwareProxyClientRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::iap::v1::IdentityAwareProxyClient>
IdentityAwareProxyOAuthServiceConnection::ResetIdentityAwareProxyClientSecret(
    google::cloud::iap::v1::ResetIdentityAwareProxyClientSecretRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

Status IdentityAwareProxyOAuthServiceConnection::DeleteIdentityAwareProxyClient(
    google::cloud::iap::v1::DeleteIdentityAwareProxyClientRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

std::shared_ptr<IdentityAwareProxyOAuthServiceConnection>
MakeIdentityAwareProxyOAuthServiceConnection(Options options) {
  internal::CheckExpectedOptions<
      CommonOptionList, GrpcOptionList,
      IdentityAwareProxyOAuthServicePolicyOptionList>(options, __func__);
  options = iap_internal::IdentityAwareProxyOAuthServiceDefaultOptions(
      std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto stub = iap_internal::CreateDefaultIdentityAwareProxyOAuthServiceStub(
      background->cq(), options);
  return std::make_shared<
      iap_internal::IdentityAwareProxyOAuthServiceConnectionImpl>(
      std::move(background), std::move(stub), std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace iap
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace iap_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<iap::IdentityAwareProxyOAuthServiceConnection>
MakeIdentityAwareProxyOAuthServiceConnection(
    std::shared_ptr<IdentityAwareProxyOAuthServiceStub> stub, Options options) {
  options = IdentityAwareProxyOAuthServiceDefaultOptions(std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  return std::make_shared<
      iap_internal::IdentityAwareProxyOAuthServiceConnectionImpl>(
      std::move(background), std::move(stub), std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace iap_internal
}  // namespace cloud
}  // namespace google
