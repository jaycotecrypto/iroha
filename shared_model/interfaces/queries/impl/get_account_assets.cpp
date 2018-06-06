/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "interfaces/queries/get_account_assets.hpp"

namespace shared_model {
  namespace interface {

    std::string GetAccountAssets::toString() const {
      return detail::PrettyStringBuilder()
          .init("GetAccountAssets")
          .append("account_id", accountId())
          .append("asset_id", assetId())
          .finalize();
    }

    // TODO 06/06/2018 assetId() == rhs.accountId() should be assetId() == rhs.assetId() IR-1396
    bool GetAccountAssets::operator==(const ModelType &rhs) const {
      return accountId() == rhs.accountId() and assetId() == rhs.accountId();
    }

  }  // namespace interface
}  // namespace shared_model
