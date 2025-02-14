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
// source: google/devtools/artifactregistry/v1/service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_ARTIFACTREGISTRY_INTERNAL_ARTIFACT_REGISTRY_STUB_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_ARTIFACTREGISTRY_INTERNAL_ARTIFACT_REGISTRY_STUB_H

#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/devtools/artifactregistry/v1/service.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace artifactregistry_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class ArtifactRegistryStub {
 public:
  virtual ~ArtifactRegistryStub() = 0;

  virtual StatusOr<
      google::devtools::artifactregistry::v1::ListDockerImagesResponse>
  ListDockerImages(
      grpc::ClientContext& context,
      google::devtools::artifactregistry::v1::ListDockerImagesRequest const&
          request) = 0;

  virtual StatusOr<
      google::devtools::artifactregistry::v1::ListRepositoriesResponse>
  ListRepositories(
      grpc::ClientContext& context,
      google::devtools::artifactregistry::v1::ListRepositoriesRequest const&
          request) = 0;

  virtual StatusOr<google::devtools::artifactregistry::v1::Repository>
  GetRepository(
      grpc::ClientContext& context,
      google::devtools::artifactregistry::v1::GetRepositoryRequest const&
          request) = 0;
};

class DefaultArtifactRegistryStub : public ArtifactRegistryStub {
 public:
  explicit DefaultArtifactRegistryStub(
      std::unique_ptr<google::devtools::artifactregistry::v1::ArtifactRegistry::
                          StubInterface>
          grpc_stub)
      : grpc_stub_(std::move(grpc_stub)) {}

  StatusOr<google::devtools::artifactregistry::v1::ListDockerImagesResponse>
  ListDockerImages(
      grpc::ClientContext& client_context,
      google::devtools::artifactregistry::v1::ListDockerImagesRequest const&
          request) override;

  StatusOr<google::devtools::artifactregistry::v1::ListRepositoriesResponse>
  ListRepositories(
      grpc::ClientContext& client_context,
      google::devtools::artifactregistry::v1::ListRepositoriesRequest const&
          request) override;

  StatusOr<google::devtools::artifactregistry::v1::Repository> GetRepository(
      grpc::ClientContext& client_context,
      google::devtools::artifactregistry::v1::GetRepositoryRequest const&
          request) override;

 private:
  std::unique_ptr<
      google::devtools::artifactregistry::v1::ArtifactRegistry::StubInterface>
      grpc_stub_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace artifactregistry_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_ARTIFACTREGISTRY_INTERNAL_ARTIFACT_REGISTRY_STUB_H
