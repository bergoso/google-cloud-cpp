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
// source: google/cloud/redis/v1/cloud_redis.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REDIS_MOCKS_MOCK_CLOUD_REDIS_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REDIS_MOCKS_MOCK_CLOUD_REDIS_CONNECTION_H

#include "google/cloud/redis/cloud_redis_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace redis_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class MockCloudRedisConnection : public redis::CloudRedisConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(StreamRange<google::cloud::redis::v1::Instance>, ListInstances,
              (google::cloud::redis::v1::ListInstancesRequest request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::redis::v1::Instance>, GetInstance,
              (google::cloud::redis::v1::GetInstanceRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::redis::v1::Instance>>,
              CreateInstance,
              (google::cloud::redis::v1::CreateInstanceRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::redis::v1::Instance>>,
              UpdateInstance,
              (google::cloud::redis::v1::UpdateInstanceRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::redis::v1::Instance>>,
              UpgradeInstance,
              (google::cloud::redis::v1::UpgradeInstanceRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::redis::v1::Instance>>,
              ImportInstance,
              (google::cloud::redis::v1::ImportInstanceRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::redis::v1::Instance>>,
              ExportInstance,
              (google::cloud::redis::v1::ExportInstanceRequest const& request),
              (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::redis::v1::Instance>>, FailoverInstance,
      (google::cloud::redis::v1::FailoverInstanceRequest const& request),
      (override));

  MOCK_METHOD(future<StatusOr<google::cloud::redis::v1::OperationMetadata>>,
              DeleteInstance,
              (google::cloud::redis::v1::DeleteInstanceRequest const& request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace redis_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REDIS_MOCKS_MOCK_CLOUD_REDIS_CONNECTION_H
