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

#include "consensus/yac/cluster_order.hpp"
#include <gtest/gtest.h>

TEST(ClusterOrderTest, ClusterOrderOnNext) {
  iroha::model::Peer p1;
  p1.address = "1";
  iroha::model::Peer p2;
  p2.address = "2";
  std::vector<iroha::model::Peer> peers = {p1, p2};
  iroha::consensus::yac::ClusterOrdering order(peers);
  ASSERT_EQ("1", order.currentLeader().address);
  ASSERT_EQ("2", order.switchToNext().currentLeader().address);
  ASSERT_EQ("1", order.switchToNext().currentLeader().address);
}

TEST(ClusterOrderTest, ClusterOrderLeaderSet) {
  iroha::model::Peer p;
  std::vector<iroha::model::Peer> peers = {p, p, p, p, p, p, p};
  iroha::consensus::yac::ClusterOrdering order(peers);
  ASSERT_TRUE(order.leaderInValidateSet());  // 1
  order.switchToNext();
  ASSERT_TRUE(order.leaderInValidateSet());  // 2
  order.switchToNext();
  ASSERT_TRUE(order.leaderInValidateSet());  // 3
  order.switchToNext();
  ASSERT_TRUE(order.leaderInValidateSet());  // 4
  order.switchToNext();
  ASSERT_TRUE(order.leaderInValidateSet());  // 5
  order.switchToNext();
  ASSERT_FALSE(order.leaderInValidateSet());  // 6
  order.switchToNext();
  ASSERT_FALSE(order.leaderInValidateSet());  // 7
  order.switchToNext();
}

TEST(ClusterOrderTest, ClusterOrderSupermajority) {
  iroha::model::Peer p;
  std::vector<iroha::model::Peer> peers = {p, p, p, p, p, p, p};
  iroha::consensus::yac::ClusterOrdering order(peers);
  ASSERT_FALSE(order.haveSupermajority(1));  // 1
  ASSERT_FALSE(order.haveSupermajority(2));  // 2
  ASSERT_FALSE(order.haveSupermajority(3));  // 3
  ASSERT_FALSE(order.haveSupermajority(4));  // 4
  ASSERT_TRUE(order.haveSupermajority(5));   // 5
  ASSERT_TRUE(order.haveSupermajority(6));   // 6
  ASSERT_TRUE(order.haveSupermajority(7));   // 7
}

TEST(ClusterOrderTest, CluserOrderSupermajorityWhenEmpty) {
  iroha::consensus::yac::ClusterOrdering order;
  ASSERT_FALSE(order.haveSupermajority(1));  // 1
  ASSERT_FALSE(order.haveSupermajority(2));  // 2
  ASSERT_FALSE(order.haveSupermajority(3));  // 3
  ASSERT_FALSE(order.haveSupermajority(4));  // 4
  ASSERT_FALSE(order.haveSupermajority(5));  // 5
  ASSERT_FALSE(order.haveSupermajority(6));  // 6
  ASSERT_FALSE(order.haveSupermajority(7));  // 7
}