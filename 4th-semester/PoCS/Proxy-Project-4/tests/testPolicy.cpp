#include <gtest/gtest.h>
#include "LRUPolicy.h"
#include "FIFOPolicy.h"

// lru

TEST(LRUPolicyTest, LRU_EmptyEvict) {
    LRUPolicy policy;
    EXPECT_EQ(policy.getCandidateToEvict(), "");
}

TEST(LRUPolicyTest, LRU_SingleItem) {
    LRUPolicy policy;
    policy.insert("key1", 10);
    EXPECT_EQ(policy.getCandidateToEvict(), "key1");
    EXPECT_EQ(policy.getCandidateToEvict(), "");
}

TEST(LRUPolicyTest, LRU_EvictionOrder) {
    LRUPolicy policy;
    policy.insert("A", 10);
    policy.insert("B", 20);
    policy.insert("C", 30);
    
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
    EXPECT_EQ(policy.getCandidateToEvict(), "B");
    EXPECT_EQ(policy.getCandidateToEvict(), "C");
}

TEST(LRUPolicyTest, LRU_TouchReorder) {
    LRUPolicy policy;
    policy.insert("A", 10);
    policy.insert("B", 20);
    policy.insert("C", 30);
    
    policy.touch("A");
    
    EXPECT_EQ(policy.getCandidateToEvict(), "B");
    EXPECT_EQ(policy.getCandidateToEvict(), "C");
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
}

TEST(LRUPolicyTest, LRU_EraseItem) {
    LRUPolicy policy;
    policy.insert("A", 10);
    policy.insert("B", 20);
    policy.insert("C", 30);
    
    policy.erase("B");
    
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
    EXPECT_EQ(policy.getCandidateToEvict(), "C");
}

TEST(LRUPolicyTest, LRU_DoubleInsert) {
    LRUPolicy policy;
    policy.insert("A", 10);
    policy.insert("A", 20);
    
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
    EXPECT_EQ(policy.getCandidateToEvict(), "");
}

TEST(LRUPolicyTest, LRU_Name) {
    LRUPolicy policy;
    EXPECT_EQ(policy.getName(), "LRU");
}

// fifo

TEST(FIFOPolicyTest, FIFO_EmptyEvict) {
    FIFOPolicy policy;
    EXPECT_EQ(policy.getCandidateToEvict(), "");
}

TEST(FIFOPolicyTest, FIFO_SingleItem) {
    FIFOPolicy policy;
    policy.insert("key1", 10);
    EXPECT_EQ(policy.getCandidateToEvict(), "key1");
    EXPECT_EQ(policy.getCandidateToEvict(), "");
}

TEST(FIFOPolicyTest, FIFO_EvictionOrder) {
    FIFOPolicy policy;
    policy.insert("A", 10);
    policy.insert("B", 20);
    policy.insert("C", 30);
    
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
    EXPECT_EQ(policy.getCandidateToEvict(), "B");
    EXPECT_EQ(policy.getCandidateToEvict(), "C");
}

TEST(FIFOPolicyTest, FIFO_TouchDoesNotReorder) {
    FIFOPolicy policy;
    policy.insert("A", 10);
    policy.insert("B", 20);
    policy.insert("C", 30);
    
    policy.touch("A");
    
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
    EXPECT_EQ(policy.getCandidateToEvict(), "B");
    EXPECT_EQ(policy.getCandidateToEvict(), "C");
}

TEST(FIFOPolicyTest, FIFO_EraseItem) {
    FIFOPolicy policy;
    policy.insert("A", 10);
    policy.insert("B", 20);
    policy.insert("C", 30);
    
    policy.erase("B");
    
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
    EXPECT_EQ(policy.getCandidateToEvict(), "C");
}

TEST(FIFOPolicyTest, FIFO_DoubleInsert) {
    FIFOPolicy policy;
    policy.insert("A", 10);
    policy.insert("A", 20);
    
    EXPECT_EQ(policy.getCandidateToEvict(), "A");
    EXPECT_EQ(policy.getCandidateToEvict(), "");
}

TEST(FIFOPolicyTest, FIFO_Name) {
    FIFOPolicy policy;
    EXPECT_EQ(policy.getName(), "FIFO");
}
