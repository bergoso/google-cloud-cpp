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
// source: google/cloud/bigquery/connection/v1/connection.proto

#include "google/cloud/bigquery/connection_connection.h"
#include "google/cloud/bigquery/connection_options.h"
#include "google/cloud/bigquery/internal/connection_connection_impl.h"
#include "google/cloud/bigquery/internal/connection_option_defaults.h"
#include "google/cloud/bigquery/internal/connection_stub_factory.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include <memory>

namespace google {
namespace cloud {
namespace bigquery {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ConnectionServiceConnection::~ConnectionServiceConnection() = default;

StatusOr<google::cloud::bigquery::connection::v1::Connection>
ConnectionServiceConnection::CreateConnection(
    google::cloud::bigquery::connection::v1::CreateConnectionRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::bigquery::connection::v1::Connection>
ConnectionServiceConnection::GetConnection(
    google::cloud::bigquery::connection::v1::GetConnectionRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::bigquery::connection::v1::Connection>
    ConnectionServiceConnection::ListConnections(
        google::cloud::bigquery::connection::v1::
            ListConnectionsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::bigquery::connection::v1::Connection>>();
}

StatusOr<google::cloud::bigquery::connection::v1::Connection>
ConnectionServiceConnection::UpdateConnection(
    google::cloud::bigquery::connection::v1::UpdateConnectionRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

Status ConnectionServiceConnection::DeleteConnection(
    google::cloud::bigquery::connection::v1::DeleteConnectionRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::Policy> ConnectionServiceConnection::GetIamPolicy(
    google::iam::v1::GetIamPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::Policy> ConnectionServiceConnection::SetIamPolicy(
    google::iam::v1::SetIamPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::TestIamPermissionsResponse>
ConnectionServiceConnection::TestIamPermissions(
    google::iam::v1::TestIamPermissionsRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

std::shared_ptr<ConnectionServiceConnection> MakeConnectionServiceConnection(
    Options options) {
  internal::CheckExpectedOptions<CommonOptionList, GrpcOptionList,
                                 ConnectionServicePolicyOptionList>(options,
                                                                    __func__);
  options =
      bigquery_internal::ConnectionServiceDefaultOptions(std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto stub = bigquery_internal::CreateDefaultConnectionServiceStub(
      background->cq(), options);
  return std::make_shared<bigquery_internal::ConnectionServiceConnectionImpl>(
      std::move(background), std::move(stub), std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigquery
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace bigquery_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<bigquery::ConnectionServiceConnection>
MakeConnectionServiceConnection(std::shared_ptr<ConnectionServiceStub> stub,
                                Options options) {
  options = ConnectionServiceDefaultOptions(std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  return std::make_shared<bigquery_internal::ConnectionServiceConnectionImpl>(
      std::move(background), std::move(stub), std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigquery_internal
}  // namespace cloud
}  // namespace google
