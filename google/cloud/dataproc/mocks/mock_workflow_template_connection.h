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
// source: google/cloud/dataproc/v1/workflow_templates.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DATAPROC_MOCKS_MOCK_WORKFLOW_TEMPLATE_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DATAPROC_MOCKS_MOCK_WORKFLOW_TEMPLATE_CONNECTION_H

#include "google/cloud/dataproc/workflow_template_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace dataproc_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class MockWorkflowTemplateServiceConnection
    : public dataproc::WorkflowTemplateServiceConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(StatusOr<google::cloud::dataproc::v1::WorkflowTemplate>,
              CreateWorkflowTemplate,
              (google::cloud::dataproc::v1::CreateWorkflowTemplateRequest const&
                   request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::dataproc::v1::WorkflowTemplate>,
      GetWorkflowTemplate,
      (google::cloud::dataproc::v1::GetWorkflowTemplateRequest const& request),
      (override));

  MOCK_METHOD(
      future<StatusOr<google::cloud::dataproc::v1::WorkflowMetadata>>,
      InstantiateWorkflowTemplate,
      (google::cloud::dataproc::v1::InstantiateWorkflowTemplateRequest const&
           request),
      (override));

  MOCK_METHOD(future<StatusOr<google::cloud::dataproc::v1::WorkflowMetadata>>,
              InstantiateInlineWorkflowTemplate,
              (google::cloud::dataproc::v1::
                   InstantiateInlineWorkflowTemplateRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::dataproc::v1::WorkflowTemplate>,
              UpdateWorkflowTemplate,
              (google::cloud::dataproc::v1::UpdateWorkflowTemplateRequest const&
                   request),
              (override));

  MOCK_METHOD(
      StreamRange<google::cloud::dataproc::v1::WorkflowTemplate>,
      ListWorkflowTemplates,
      (google::cloud::dataproc::v1::ListWorkflowTemplatesRequest request),
      (override));

  MOCK_METHOD(Status, DeleteWorkflowTemplate,
              (google::cloud::dataproc::v1::DeleteWorkflowTemplateRequest const&
                   request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dataproc_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DATAPROC_MOCKS_MOCK_WORKFLOW_TEMPLATE_CONNECTION_H
