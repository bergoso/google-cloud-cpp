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
// source: google/cloud/gaming/v1/game_server_configs_service.proto

#include "google/cloud/gameservices/game_server_configs_connection_idempotency_policy.h"
#include "absl/memory/memory.h"
#include <memory>

namespace google {
namespace cloud {
namespace gameservices {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using ::google::cloud::Idempotency;

GameServerConfigsServiceConnectionIdempotencyPolicy::
    ~GameServerConfigsServiceConnectionIdempotencyPolicy() = default;

namespace {
class DefaultGameServerConfigsServiceConnectionIdempotencyPolicy
    : public GameServerConfigsServiceConnectionIdempotencyPolicy {
 public:
  ~DefaultGameServerConfigsServiceConnectionIdempotencyPolicy() override =
      default;

  /// Create a new copy of this object.
  std::unique_ptr<GameServerConfigsServiceConnectionIdempotencyPolicy> clone()
      const override {
    return absl::make_unique<
        DefaultGameServerConfigsServiceConnectionIdempotencyPolicy>(*this);
  }

  Idempotency ListGameServerConfigs(
      google::cloud::gaming::v1::ListGameServerConfigsRequest) override {
    return Idempotency::kIdempotent;
  }

  Idempotency GetGameServerConfig(
      google::cloud::gaming::v1::GetGameServerConfigRequest const&) override {
    return Idempotency::kIdempotent;
  }

  Idempotency CreateGameServerConfig(
      google::cloud::gaming::v1::CreateGameServerConfigRequest const&)
      override {
    return Idempotency::kNonIdempotent;
  }

  Idempotency DeleteGameServerConfig(
      google::cloud::gaming::v1::DeleteGameServerConfigRequest const&)
      override {
    return Idempotency::kNonIdempotent;
  }
};
}  // namespace

std::unique_ptr<GameServerConfigsServiceConnectionIdempotencyPolicy>
MakeDefaultGameServerConfigsServiceConnectionIdempotencyPolicy() {
  return absl::make_unique<
      DefaultGameServerConfigsServiceConnectionIdempotencyPolicy>();
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace gameservices
}  // namespace cloud
}  // namespace google
