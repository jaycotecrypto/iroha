/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_GET_ACCOUNT_ASSETS_HPP
#define IROHA_GET_ACCOUNT_ASSETS_HPP

#include "interfaces/common_objects/types.hpp"
#include "interfaces/hashable.hpp"
#include "model/queries/get_account_assets.hpp"

namespace shared_model {
  namespace interface {
    /**
     * Query for get all account's assets and balance
     */
    class GetAccountAssets
        : public Hashable<GetAccountAssets, iroha::model::GetAccountAssets> {
      virtual const types::AccountIdType &accountId() const = 0;
      virtual const types::AssetIdType &assetId() const = 0;

      virtual OldModelType *makeOldModel() const {
        auto oldModel = new iroha::model::GetAccountAssets;
        oldModel->account_id = accountId();
        oldModel->asset_id = assetId();
        return oldModel;
      }

      virtual std::string toString() const {
        //TODO 30/10/2017 kamilsa implement to string with builders
        return Primitive::toString();
      }
    };
  }  // namespace interface
}  // namespace shared_model

#endif  // IROHA_GET_ACCOUNT_ASSETS_HPP
