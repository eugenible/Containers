#include <gtest/gtest.h>

#include <list>
#include <queue>
#include <stack>

#include "s21_containers.h"
#include "s21_containersplus.h"

TEST(Testing_stack, test_1) {
  s21::stack<int> my_stack;
  std::stack<int> origin_stack;

  EXPECT_EQ(origin_stack.size(), my_stack.size());
}

TEST(Testing_stack, test_2) {
  s21::stack<int> my_stack;
  std::stack<int> origin_stack;

  my_stack.push(5);
  origin_stack.push(5);

  EXPECT_EQ(origin_stack.size(), my_stack.size());
}

TEST(Testing_stack, test_3) {
  s21::stack<int> my_stack = {1, 2, 3, 4, 5};
  std::stack<int> origin_stack;
  for (int i = 1; i < 6; i++) {
    origin_stack.push(i);
  }

  EXPECT_EQ(origin_stack.size(), my_stack.size());
  EXPECT_EQ(origin_stack.top(), my_stack.top());
}

TEST(Testing_stack, test_4) {
  s21::stack<int> my_stack = {1, 2, 3, 4, 5};

  s21::stack<int> copy_stack(my_stack);

  EXPECT_EQ(my_stack.size(), copy_stack.size());
  EXPECT_EQ(my_stack.top(), copy_stack.top());
}

TEST(Testing_stack, test_5) {
  s21::stack<int> my_stack = {1, 2, 3, 4, 5};
  std::stack<int> origin_stack;

  for (int i = 1; i < 6; i++) {
    origin_stack.push(i);
  }

  s21::stack<int> copy_stack(std::move(my_stack));

  EXPECT_EQ(origin_stack.size(), copy_stack.size());
  EXPECT_EQ(origin_stack.top(), copy_stack.top());
  EXPECT_ANY_THROW(my_stack.top());
}

TEST(Testing_stack, test_6) {
  s21::stack<int> my_stack = {1, 2, 3, 4, 5};
  std::stack<int> origin_stack;

  for (int i = 1; i < 6; i++) {
    origin_stack.push(i);
  }

  s21::stack<int> copy_stack = std::move(my_stack);

  EXPECT_EQ(origin_stack.size(), copy_stack.size());
  EXPECT_EQ(origin_stack.top(), copy_stack.top());
  EXPECT_ANY_THROW(my_stack.top());
}

TEST(Testing_stack, test_7) {
  s21::stack<int> my_stack = {1, 2, 3, 4, 5};

  while (!my_stack.empty()) {
    my_stack.pop();
  }
  EXPECT_TRUE(my_stack.empty());
  my_stack.push(333);
  EXPECT_FALSE(my_stack.empty());
}

TEST(Testing_stack, test_8) {
  s21::stack<int> my_stack = {1, 2, 3, 4, 5};

  EXPECT_EQ(my_stack.size(), 5);
}

TEST(Testing_stack, test_9) {
  s21::stack<int> my_stack_1 = {1, 2, 3, 4, 5};
  s21::stack<int> my_stack_2 = {6, 7, 8, 9, 10};

  my_stack_1.swap(my_stack_2);

  EXPECT_EQ(my_stack_1.top(), 10);
  EXPECT_EQ(my_stack_2.top(), 5);
}

TEST(Testing_stack, test_10) {
  s21::stack<int> my_stack;
  my_stack.emplace_front(5, 6, 7, 8, 9, 10);
  EXPECT_EQ(my_stack.top(), 10);
}

TEST(Testing_stack, test_11) {
  s21::stack<int> my_stack = {1, 2};
  my_stack.push(3);
  my_stack.emplace_front(5, 6, 7, 8, 9, 10);
  EXPECT_EQ(my_stack.top(), 10);
}

TEST(Testing_stack, test_12) {
  s21::stack<int> my_stack1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::stack<int> my_stack2 = std::move(my_stack1);
  EXPECT_EQ(my_stack2.top(), 10);
  EXPECT_TRUE(my_stack1.empty());
}

TEST(Testing_stack, Testing_array_test_13_Test) {
  s21::stack<int> my_stack1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  my_stack1 = std::move(my_stack1);
  EXPECT_EQ(my_stack1.top(), 10);
  EXPECT_FALSE(my_stack1.empty());
}

TEST(Testing_queue, test_1) {
  s21::queue<int> my_queue;
  std::queue<int> origin_queue;

  EXPECT_EQ(origin_queue.size(), my_queue.size());
}

TEST(Testing_queue, test_2) {
  s21::queue<int> my_queue;
  std::queue<int> origin_queue;

  my_queue.push(5);
  origin_queue.push(5);

  EXPECT_EQ(origin_queue.size(), my_queue.size());
}

TEST(Testing_queue, test_3) {
  s21::queue<int> my_queue;
  for (int i = 1; i < 6; i++) {
    my_queue.push(i);
  }
  std::queue<int> origin_queue;
  for (int i = 1; i < 6; i++) {
    origin_queue.push(i);
  }

  EXPECT_EQ(origin_queue.size(), my_queue.size());
  EXPECT_EQ(origin_queue.front(), my_queue.front());
  EXPECT_EQ(origin_queue.back(), my_queue.back());
}

TEST(Testing_queue, test_4) {
  s21::queue<int> my_queue;

  for (int i = 1; i < 6; i++) {
    my_queue.push(i);
  }

  s21::queue<int> copy_stack(my_queue);

  EXPECT_EQ(my_queue.size(), copy_stack.size());
  EXPECT_EQ(copy_stack.front(), copy_stack.front());
  EXPECT_EQ(copy_stack.back(), my_queue.back());
}

TEST(Testing_queue, test_5) {
  s21::queue<int> my_queue;
  for (int i = 1; i < 6; i++) {
    my_queue.push(i);
  }
  std::queue<int> origin_queue;

  for (int i = 1; i < 6; i++) {
    origin_queue.push(i);
  }

  s21::queue<int> copy_queue(std::move(my_queue));

  EXPECT_EQ(origin_queue.size(), copy_queue.size());
  EXPECT_EQ(origin_queue.front(), copy_queue.front());
  EXPECT_EQ(origin_queue.back(), copy_queue.back());
  EXPECT_ANY_THROW(my_queue.front());
}

TEST(Testing_queue, test_6) {
  s21::queue<int> my_queue;
  for (int i = 1; i < 6; i++) {
    my_queue.push(i);
  }
  std::queue<int> origin_queue;

  for (int i = 1; i < 6; i++) {
    origin_queue.push(i);
  }

  s21::queue<int> copy_queue = std::move(my_queue);

  EXPECT_EQ(origin_queue.size(), copy_queue.size());
  EXPECT_EQ(origin_queue.front(), copy_queue.front());
  EXPECT_EQ(origin_queue.back(), copy_queue.back());
  EXPECT_ANY_THROW(my_queue.front());
  EXPECT_ANY_THROW(my_queue.back());
}

TEST(Testing_queue, test_7) {
  s21::queue<int> my_queue = {1, 2, 3, 4, 5};

  while (!my_queue.empty()) {
    my_queue.pop();
  }
  EXPECT_TRUE(my_queue.empty());
  my_queue.push(333);
  EXPECT_FALSE(my_queue.empty());
}

TEST(Testing_queue, test_8) {
  s21::queue<int> my_queue;
  for (int i = 1; i < 6; i++) {
    my_queue.push(i);
  }
  EXPECT_EQ(my_queue.size(), 5);
  EXPECT_EQ(my_queue.front(), 1);
  EXPECT_EQ(my_queue.back(), 5);
}

TEST(Testing_queue, test_9) {
  s21::queue<int> my_queue_1;
  s21::queue<int> my_queue_2;
  for (int i = 1; i < 6; i++) {
    my_queue_1.push(i);
  }
  for (int i = 6; i < 11; i++) {
    my_queue_2.push(i);
  }
  my_queue_1.swap(my_queue_2);

  EXPECT_EQ(my_queue_1.front(), 6);
  EXPECT_EQ(my_queue_1.back(), 10);
  EXPECT_EQ(my_queue_2.front(), 1);
  EXPECT_EQ(my_queue_2.back(), 5);
}

TEST(Testing_queue, test_10) {
  s21::queue<int> my_queue;
  my_queue.emplace_back(1, 2, 3, 4, 5, 6);
  EXPECT_EQ(my_queue.front(), 1);
  EXPECT_EQ(my_queue.back(), 6);
}

TEST(Testing_queue, test_11) {
  s21::queue<int> my_queue1 = {1, 2, 3, 4, 5, 6};
  s21::queue<int> my_queue2 = std::move(my_queue1);
  EXPECT_EQ(my_queue2.front(), 1);
  EXPECT_EQ(my_queue2.back(), 6);
}

TEST(Testing_queue, test_12) {
  s21::queue<int> my_queue1 = {1, 2, 3, 4, 5, 6};
  my_queue1 = std::move(my_queue1);
  EXPECT_EQ(my_queue1.front(), 1);
  EXPECT_EQ(my_queue1.back(), 6);
}

TEST(Testing_list, test_1) {
  s21::list<int> my_list;
  std::list<int> origin_list;

  EXPECT_EQ(origin_list.size(), my_list.size());
}

TEST(Testing_list, test_2) {
  s21::list<int> my_list;
  std::list<int> origin_list;
  for (int i = 1; i < 5; i++) {
    my_list.push_front(i);
  }
  for (int i = 1; i < 5; i++) {
    origin_list.push_front(i);
  }
  my_list.push_front(5);
  origin_list.push_front(5);

  EXPECT_EQ(origin_list.size(), my_list.size());
}

TEST(Testing_list, test_3) {
  s21::list<int> my_list;
  std::list<int> origin_list;
  for (int i = 1; i < 5; i++) {
    my_list.push_back(i);
  }
  for (int i = 1; i < 5; i++) {
    origin_list.push_back(i);
  }
  my_list.push_back(5);
  origin_list.push_back(5);

  EXPECT_EQ(origin_list.size(), my_list.size());
}

TEST(Testing_list, test_4) {
  s21::list<int> my_list;
  for (int i = 1; i < 6; i++) {
    my_list.push_front(i);
  }
  std::list<int> origin_list;
  for (int i = 1; i < 6; i++) {
    origin_list.push_front(i);
  }

  EXPECT_EQ(origin_list.size(), my_list.size());
  EXPECT_EQ(origin_list.front(), my_list.front());
  EXPECT_EQ(origin_list.back(), my_list.back());
}

TEST(Testing_list, test_5) {
  s21::list<int> my_list;

  for (int i = 1; i < 6; i++) {
    my_list.push_front(i);
  }

  s21::list<int> copy_list(my_list);

  EXPECT_EQ(my_list.size(), copy_list.size());
  EXPECT_EQ(copy_list.front(), my_list.front());
  EXPECT_EQ(copy_list.back(), my_list.back());
}

TEST(Testing_list, test_6) {
  s21::list<int> my_list;
  for (int i = 1; i < 6; i++) {
    my_list.push_front(i);
  }
  std::list<int> origin_list;

  for (int i = 1; i < 6; i++) {
    origin_list.push_front(i);
  }

  s21::list<int> copy_list(std::move(my_list));

  EXPECT_EQ(origin_list.size(), copy_list.size());
  EXPECT_EQ(origin_list.front(), copy_list.front());
  EXPECT_EQ(origin_list.back(), copy_list.back());
  EXPECT_ANY_THROW(my_list.front());
}

TEST(Testing_list, test_7) {
  s21::list<int> my_list;
  for (int i = 1; i < 6; i++) {
    my_list.push_front(i);
  }
  std::list<int> origin_list;

  for (int i = 1; i < 6; i++) {
    origin_list.push_front(i);
  }

  s21::list<int> copy_list = std::move(my_list);

  EXPECT_EQ(origin_list.size(), copy_list.size());
  EXPECT_EQ(origin_list.front(), copy_list.front());
  EXPECT_EQ(origin_list.back(), copy_list.back());
  EXPECT_ANY_THROW(my_list.front());
  EXPECT_ANY_THROW(my_list.back());
}

TEST(Testing_list, test_8) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};

  my_list.pop_front();
  EXPECT_EQ(my_list.front(), 2);
  while (!my_list.empty()) {
    my_list.pop_front();
  }
  EXPECT_TRUE(my_list.empty());
  my_list.push_front(333);
  EXPECT_FALSE(my_list.empty());
}

TEST(Testing_list, test_9) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};

  my_list.pop_back();
  EXPECT_EQ(my_list.back(), 4);
  while (!my_list.empty()) {
    my_list.pop_back();
  }
  EXPECT_TRUE(my_list.empty());
  my_list.push_back(333);
  EXPECT_FALSE(my_list.empty());
}

TEST(Testing_list, test_10) {
  s21::list<int> my_list_1;
  s21::list<int> my_list_2;
  for (int i = 1; i < 6; i++) {
    my_list_1.push_front(i);
  }
  for (int i = 6; i < 11; i++) {
    my_list_2.push_front(i);
  }
  my_list_1.swap(my_list_2);

  EXPECT_EQ(my_list_1.front(), 10);
  EXPECT_EQ(my_list_1.back(), 6);
  EXPECT_EQ(my_list_2.front(), 5);
  EXPECT_EQ(my_list_2.back(), 1);
}

TEST(Testing_list, test_11) {
  s21::list<int> my_list_1;
  s21::list<int> my_list_2;
  for (int i = 1; i < 6; i++) {
    my_list_1.push_back(i);
  }
  for (int i = 6; i < 11; i++) {
    my_list_2.push_back(i);
  }
  my_list_1.merge(my_list_2);

  EXPECT_EQ(my_list_1.front(), 1);
  EXPECT_EQ(my_list_1.back(), 10);
  EXPECT_ANY_THROW(my_list_2.front());
  EXPECT_ANY_THROW(my_list_2.back());
}

TEST(Testing_list, test_12) {
  s21::list<int> my_list_1;
  s21::list<int> my_list_2;
  for (int i = 6; i < 11; i++) {
    my_list_1.push_back(i);
  }
  for (int i = 1; i < 6; i++) {
    my_list_2.push_back(i);
  }
  my_list_1.merge(my_list_2);

  EXPECT_EQ(my_list_1.front(), 1);
  EXPECT_EQ(my_list_1.back(), 10);
  EXPECT_ANY_THROW(my_list_2.front());
  EXPECT_ANY_THROW(my_list_2.back());
}

TEST(Testing_list, test_13) {
  s21::list<int> my_list_1;
  s21::list<int> my_list_2;
  for (int i = 1; i < 6; i++) {
    my_list_1.push_back(i);
  }
  for (int i = 1; i < 6; i++) {
    my_list_2.push_back(i);
  }
  s21::list<int>::iterator it = my_list_1.begin();
  s21::list<int>::iterator it_2 = my_list_2.begin();
  ++it;
  ++it_2;
  --it;
  --it_2;
  EXPECT_EQ(*it, *it_2);
}

TEST(Testing_list, test_14) {
  s21::list<int> my_list_1;
  s21::list<int> my_list_2;
  for (int i = 1; i < 6; i++) {
    my_list_1.push_back(i);
  }
  for (int i = 1; i < 6; i++) {
    my_list_2.push_back(i);
  }
  s21::list<int>::iterator it = my_list_1.end();
  s21::list<int>::iterator it_2 = my_list_2.begin();
  my_list_1.insert(it, 90);
  my_list_2.insert(it_2, 90);
  EXPECT_EQ(my_list_1.back(), my_list_2.front());
}

TEST(Testing_list, test_15) {
  s21::list<int> my_list_1;
  s21::list<int> my_list_2;
  for (int i = 1; i < 6; i++) {
    my_list_1.push_back(i);
  }
  for (int i = 1; i < 6; i++) {
    my_list_2.push_back(i);
  }
  s21::list<int>::iterator it = my_list_1.begin();
  s21::list<int>::iterator it_2 = my_list_2.begin();
  ++it;
  ++it_2;
  my_list_1.insert(it, 90);
  my_list_2.insert(it_2, 90);
  EXPECT_EQ(my_list_1.front(), my_list_2.front());
}

TEST(Testing_list, test_16) {
  s21::list<int> my_list_1;

  for (int i = 1; i < 6; i++) {
    my_list_1.push_back(i);
  }

  my_list_1.reverse();
  EXPECT_EQ(my_list_1.front(), 5);
  EXPECT_EQ(my_list_1.back(), 1);
}

TEST(Testing_list, test_17) {
  s21::list<int> my_list_1 = {3, 5, 1, 2, 4};
  my_list_1.sort();
  EXPECT_EQ(my_list_1.front(), 1);
  EXPECT_EQ(my_list_1.back(), 5);
}

TEST(Testing_list, test_18) {
  s21::list<int> my_list_1 = {1, 2, 3, 3, 3, 3, 3, 3, 4, 5};
  my_list_1.unique();
  for (int i = 1; i < 6; ++i) {
    EXPECT_EQ(my_list_1.front(), i);
    my_list_1.pop_front();
  }
}

TEST(Testing_list, test_19) {
  s21::list<int> my_list_1 = {1, 1, 1, 1, 1, 1, 1};
  my_list_1.unique();
  EXPECT_EQ(my_list_1.front(), 1);
  EXPECT_EQ(my_list_1.size(), 1);
}

TEST(Testing_list, test_19_1) {
  s21::list<int> my_list_1 = {1};
  my_list_1.erase(my_list_1.begin());
  EXPECT_TRUE(my_list_1.empty());
}

TEST(Testing_list, test_20) {
  s21::list<int> my_list_1 = {1, 2};
  s21::list<int>::iterator it = my_list_1.begin();
  ++it;
  my_list_1.erase(it);
  EXPECT_EQ(my_list_1.size(), 1);
}

TEST(Testing_list, test_21) {
  s21::list<int> my_list_1(5);
  EXPECT_EQ(my_list_1.size(), 5);
}

TEST(Testing_list, test_22) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.max_size(), std_list.max_size());
}

TEST(Testing_list, test_23) {
  s21::list<int> my_list_1 = {1, 2};
  s21::list<int>::iterator it = my_list_1.begin();
  ++it;
  my_list_1.insert(it, 555);
  EXPECT_EQ(my_list_1.size(), 3);
}

TEST(Testing_list, test_24) {
  s21::list<int> my_list_1;
  my_list_1.push_back(1);
  my_list_1.push_back(2);
  s21::list<int>::iterator it = my_list_1.begin();
  my_list_1.erase(it);
  EXPECT_EQ(my_list_1.size(), 1);
}

TEST(Testing_list, test_25) {
  s21::list<int> my_list;
  my_list.emplace(my_list.cbegin(), 5, 6, 7);
  my_list.emplace_front(0, 1, 2, 3, 4);
  my_list.emplace_back(8, 9, 10);
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(*my_list[i], i);
  }
}

TEST(Testing_list, test_26) {
  s21::list<int> my_list = {1, 2, 3, 4, 5, 6, 7};
  int i = 1;
  for (auto it = my_list.cbegin(); it != my_list.cend(); ++it, i++) {
    EXPECT_EQ(*it, i);
  }
}

TEST(Testing_list, test_27) {
  s21::list<int> my_list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> my_list2 = std::move(my_list1);
  for (int i = 1; i < 11; i++) {
    EXPECT_EQ(*my_list2[i - 1], i);
  }
  EXPECT_TRUE(my_list1.empty());
}

TEST(Testing_list, test_28) {
  s21::list<int> my_list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  my_list1 = std::move(my_list1);
  for (int i = 1; i < 11; i++) {
    EXPECT_EQ(*my_list1[i - 1], i);
  }
  EXPECT_FALSE(my_list1.empty());
}

TEST(Testing_list, test_29) {
  s21::list<int> my_list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> my_list2 = {11, 12, 13, 14, 15, 16};
  my_list1.splice(my_list1.cbegin(), my_list2);
  for (int i = 1; i < 16; i++) {
    EXPECT_EQ(*my_list1[i - 1], i);
  }
  EXPECT_FALSE(my_list1.empty());
  EXPECT_TRUE(my_list2.empty());
}

TEST(Testing_vector, test_1) {
  s21::stack<int> my_vector;
  std::vector<int> origin_vector;

  EXPECT_EQ(origin_vector.size(), my_vector.size());
}

TEST(Testing_vector, test_2) {
  s21::vector<int> my_vector;
  std::vector<int> origin_vector;

  my_vector.push_back(5);
  origin_vector.push_back(5);

  EXPECT_EQ(origin_vector.size(), my_vector.size());
}

TEST(Testing_vector, test_3) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};
  std::vector<int> origin_vector;
  for (int i = 1; i < 6; i++) {
    origin_vector.push_back(i);
  }

  EXPECT_EQ(origin_vector.size(), my_vector.size());
  EXPECT_EQ(origin_vector.back(), my_vector.back());
}

TEST(Testing_vector, test_4) {
  s21::vector<int> my_vector;

  for (int i = 1; i < 6; i++) {
    my_vector.push_back(i);
  }

  s21::vector<int> copy_vector(my_vector);

  EXPECT_EQ(my_vector.size(), copy_vector.size());
  EXPECT_EQ(my_vector.back(), copy_vector.back());
}

TEST(Testing_vector, test_5) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};
  std::vector<int> origin_vector;

  for (int i = 1; i < 6; i++) {
    origin_vector.push_back(i);
  }

  s21::vector<int> copy_vector(std::move(my_vector));

  EXPECT_EQ(origin_vector.size(), copy_vector.size());
  EXPECT_EQ(origin_vector.back(), copy_vector.back());
  EXPECT_TRUE(my_vector.empty());
}

TEST(Testing_vector, test_6) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};
  std::vector<int> origin_vector;

  for (int i = 1; i < 6; i++) {
    origin_vector.push_back(i);
  }

  s21::vector<int> copy_vector = std::move(my_vector);

  EXPECT_EQ(origin_vector.size(), copy_vector.size());
  EXPECT_EQ(origin_vector.back(), copy_vector.back());
  EXPECT_TRUE(my_vector.empty());
}

TEST(Testing_vector, test_7) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};

  while (!my_vector.empty()) {
    my_vector.pop_back();
  }
  EXPECT_TRUE(my_vector.empty());
  my_vector.push_back(333);
  EXPECT_FALSE(my_vector.empty());
}

TEST(Testing_vector, test_8) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};

  EXPECT_EQ(my_vector.size(), 5);
}

TEST(Testing_vector, test_9) {
  s21::vector<int> my_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> my_vector2(my_vector1);
  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(my_vector1[i - 1], my_vector2[i - 1]);
  }
  EXPECT_EQ(my_vector1.size(), 5);
  EXPECT_EQ(my_vector2.size(), 5);
}

TEST(Testing_vector, test_10) {
  s21::vector<int> my_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> my_vector2 = std::move(my_vector1);
  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(my_vector2[i - 1], i);
  }
  EXPECT_TRUE(my_vector1.empty());
  EXPECT_EQ(my_vector2.size(), 5);
}

TEST(Testing_vector, test_11) {
  s21::vector<int> my_vector1 = {1, 2, 3, 4, 5};
  my_vector1 = std::move(my_vector1);
  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(my_vector1[i - 1], i);
  }
  EXPECT_EQ(my_vector1.at(2), 3);
  EXPECT_EQ(my_vector1.size(), 5);
}

TEST(Testing_vector, test_12) {
  s21::vector<int> my_vector1 = {2, 3, 4, 5, 6};
  my_vector1.insert(my_vector1.begin(), 1);
  for (int i = 1; i < 7; i++) {
    EXPECT_EQ(my_vector1[i - 1], i);
  }
  my_vector1.shrink_to_fit();
  EXPECT_EQ(my_vector1.size(), 6);
  EXPECT_EQ(my_vector1.capacity(), 6);
}

TEST(Testing_vector, test_13) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  my_vector.erase(my_vector.begin());
  EXPECT_EQ(my_vector.front(), 2);
  EXPECT_EQ(my_vector.back(), 10);
  my_vector.reserve(100);
  EXPECT_EQ(my_vector.capacity(), 100);
}

TEST(Testing_vector, test_14) {
  s21::vector<int> my_vector;
  for (int i = 0; i < 1000; i++) {
    my_vector.insert(my_vector.begin(), i);
  }
  for (int i = 0; i < 1000; i++) {
    my_vector.erase(my_vector.begin());
  }
  EXPECT_TRUE(my_vector.empty());
}

TEST(Testing_vector, test_15) {
  s21::vector<int> my_vector(5);
  EXPECT_THROW(my_vector.at(10000000), std::out_of_range);
}

TEST(Testing_vector, test_16) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};
  auto it = my_vector.begin() + 2;
  auto i = my_vector.insert(it, -5);
  EXPECT_EQ(*i, -5);
}

TEST(Testing_vector, test_17) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};
  auto it = my_vector.begin() + 2;
  auto i = my_vector.insert(it, -5);
  EXPECT_EQ(*i, -5);
}

TEST(Testing_vector, test_18) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5};
  auto it = my_vector.begin() + 2;
  my_vector.erase(it);
  EXPECT_EQ(my_vector[2], 4);
  EXPECT_EQ(my_vector.size(), 4);
}

TEST(Testing_vector, test_19) {
  s21::vector<int> my_vector;
  my_vector.emplace(my_vector.cbegin(), 1, 2, 3, 4, 5, 6, 7, 8);
  for (int i = 1; i < 9; i++) {
    EXPECT_EQ(my_vector[i - 1], i);
  }
}

TEST(Testing_vector, test_20) {
  s21::vector<int> my_vector;
  my_vector.emplace_back(1, 2, 3, 4, 5, 6, 7, 8);
  int i = 1;
  for (auto it = my_vector.begin(); it != my_vector.end(); it++) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(Testing_vector, test_21) {
  s21::vector<int> my_vector1 = {10, 20, 30};
  s21::vector<int> my_vector2 = {1, 2, 3, 4, 5, 6, 7, 8};
  my_vector2.emplace_back(1, 2, 3, 4, 5, 6, 7, 8);
  my_vector1.swap(my_vector2);
  for (int i = 1; i < 9; i++) {
    EXPECT_EQ(my_vector1[i - 1], i);
  }
}

TEST(Testing_vector, test_22) {
  s21::vector<int> my_vector1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> std_vector = {1, 2, 3};
  EXPECT_EQ(my_vector1.max_size(), std_vector.max_size());
}

TEST(Testing_vector, test_23) {
  s21::vector<int> my_vector1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (auto it = my_vector1.cbegin(); it != my_vector1.cend(); ++it) {
    *it;
  }
  EXPECT_EQ(*my_vector1.data(), 1);
  my_vector1.clear();
  EXPECT_TRUE(my_vector1.empty());
}

TEST(Testing_map, test_1) {
  s21::map<int, int> my_map = {{1, 1}, {2, 2}, {3, 3}, {3, 3}, {2, 234234}};

  EXPECT_EQ(my_map.size(), 3);
}

TEST(Testing_map, test_2) {
  s21::map<int, int> my_map;
  EXPECT_EQ(my_map.size(), 0);
}

TEST(Testing_map, test_3) {
  s21::map<int, int> my_map;
  my_map.insert(1, 1);
  my_map.insert(2, 2);
  my_map.insert(3, 3);
  my_map.insert(2, 5555);

  s21::map<int, int>::iterator it = my_map.begin();
  my_map.erase(it);
  it = my_map.begin();
  my_map.erase(it);
  it = my_map.begin();
  my_map.erase(it);
  EXPECT_TRUE(my_map.empty());
}

TEST(Testing_map, test_4) {
  s21::map<int, int> my_map;
  my_map.insert(333, 1);
  my_map.insert(444, 2);
  my_map.insert(555, 3);
  my_map.insert(666, 4);

  EXPECT_TRUE(my_map.contains(333));
  EXPECT_FALSE(my_map.contains(-123));
  EXPECT_FALSE(my_map.contains(2));
}

TEST(Testing_map, test_5) {
  s21::map<int, int> my_map = {
      {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 2}, {3, 3},
  };

  my_map.clear();
  EXPECT_FALSE(my_map.contains(1));
  EXPECT_FALSE(my_map.contains(2));
  EXPECT_FALSE(my_map.contains(3));
  EXPECT_TRUE(my_map.empty());
}

TEST(Testing_map, test_6) {
  s21::map<int, int> my_map = {{1, 1}, {2, 2}, {3, 3}};

  my_map[1] = 111;
  std::pair<s21::map<int, int>::iterator, bool> p1 =
      my_map.insert_or_assign(2, 222);
  std::pair<s21::map<int, int>::iterator, bool> p2 =
      my_map.insert_or_assign(4, 4);

  EXPECT_EQ(p1.first->first, 2);
  EXPECT_EQ(p1.first->second, 222);

  EXPECT_EQ(p2.first->first, 4);
  EXPECT_EQ(p2.first->second, 4);

  EXPECT_EQ(my_map[1], 111);
  EXPECT_EQ(my_map[2], 222);
  EXPECT_EQ(my_map[3], 3);
  EXPECT_EQ(my_map[4], 4);

  EXPECT_EQ(my_map.at(1), 111);
  EXPECT_EQ(my_map.at(2), 222);
  EXPECT_EQ(my_map.at(3), 3);
  EXPECT_EQ(my_map.at(4), 4);
}

TEST(Testing_map, test_7) {
  s21::map<int, int> my_map = {{1, 1}, {2, 2}, {3, 3}};

  int i = 1;
  for (s21::map<int, int>::iterator it = my_map.begin(); it != my_map.end();
       ++it, i++) {
    EXPECT_EQ(it->first, i);
    EXPECT_EQ(it->second, i);
  }
}

TEST(Testing_map, test_8) {
  s21::map<int, int> my_map1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> my_map2 = {{1, 123}, {4, 4}, {5, 5}, {6, 6}};

  my_map1.merge(my_map2);
  EXPECT_EQ(my_map1[1], 1);
  EXPECT_EQ(my_map1[2], 2);
  EXPECT_EQ(my_map1[3], 3);
  EXPECT_EQ(my_map1[4], 4);
  EXPECT_EQ(my_map1[5], 5);
  EXPECT_EQ(my_map1[6], 6);

  EXPECT_EQ(my_map2[1], 123);

  EXPECT_FALSE(my_map2.contains(2));
  EXPECT_FALSE(my_map2.contains(3));
  EXPECT_FALSE(my_map2.empty());
}

TEST(Testing_map, test_9) {
  s21::map<int, int> my_map1;
  s21::map<int, int> my_map2;
  for (int i = -100; i < 100; i++) {
    my_map1.insert(i, i);
  }

  my_map2.swap(my_map1);

  int i = -100;
  for (auto it = my_map2.cbegin(); it != my_map2.cend(); ++it, i++) {
    EXPECT_EQ(it->first, i);
  }

  EXPECT_FALSE(my_map1.contains(50));
  EXPECT_TRUE(my_map2.contains(50));
  EXPECT_FALSE(my_map2.empty());
  EXPECT_TRUE(my_map1.empty());
}

TEST(Testing_map, test_10) {
  s21::map<int, int> my_map1;
  for (int i = 0; i < 10000; i++) {
    my_map1.insert(i, i);
  }
  auto it = my_map1.begin();
  for (int i = 0; i <= 1363; i++) {
    ++it;
  }
  my_map1.erase(it);
  EXPECT_FALSE(my_map1.contains(1364));
  it = my_map1.begin();
  for (int i = 0; i <= 9782; i++) {
    ++it;
  }
  my_map1.erase(it);
  EXPECT_FALSE(my_map1.contains(9784));
}

TEST(Testing_map, test_11) {
  s21::map<int, int> my_map1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> my_map2(my_map1);

  EXPECT_EQ(my_map1[1], my_map2[1]);
  EXPECT_EQ(my_map1[2], my_map2[2]);
  EXPECT_EQ(my_map1[3], my_map2[3]);
}

TEST(Testing_map, test_12) {
  s21::map<int, int> my_map = {{1, 1}, {2, 2}};
  EXPECT_THROW(my_map.at(10000), std::out_of_range);
}

TEST(Testing_map, test_13) {
  s21::map<int, int> my_map = {{1, 1}, {2, 2}};
  my_map[3] = 3;
  EXPECT_EQ(my_map[3], my_map[3]);
  EXPECT_EQ(my_map.at(3), 3);
}

TEST(Testing_map, test_14) {
  s21::map<int, int> my_map;
  s21::pair<int, int> p1 = {1, 1};
  s21::pair<int, int> p2 = {2, 2};
  s21::pair<int, int> p3 = {3, 3};
  my_map.emplace(p1, p2, p3);
  EXPECT_EQ(my_map[3], my_map[3]);
  EXPECT_EQ(my_map.at(3), 3);
}

TEST(Testing_map, test_15) {
  s21::map<int, int> my_map = {{0, 0}, {5, 5}};
  s21::pair<int, int> p1 = {1, 1};
  s21::pair<int, int> p2 = {2, 2};
  s21::pair<int, int> p3 = {3, 3};
  my_map.emplace(p1, p2, p3);
  EXPECT_EQ(my_map[3], my_map[3]);
  EXPECT_EQ(my_map.at(3), 3);
}

TEST(Testing_map, test_16) {
  s21::map<int, int> my_map1 = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> my_map2 = std::move(my_map1);

  EXPECT_EQ(my_map2[3], my_map2[3]);
  EXPECT_EQ(my_map2.at(3), 3);
}

TEST(Testing_map, test_17) {
  s21::map<int, int> my_map1 = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> my_map2 = std::move(my_map1);

  EXPECT_EQ(my_map2[3], my_map2[3]);
  EXPECT_EQ(my_map2.at(3), 3);
}

TEST(Testing_set, test_1) {
  s21::set<int> my_set = {1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 2, 3, 4};
  EXPECT_EQ(my_set.size(), 6);
  EXPECT_FALSE(my_set.empty());
}

TEST(Testing_set, test_2) {
  s21::set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  EXPECT_EQ(my_set.size(), 3);
  EXPECT_FALSE(my_set.empty());
}

TEST(Testing_set, test_3) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  my_set.clear();
  EXPECT_TRUE(my_set.empty());
}

TEST(Testing_set, test_4) {
  s21::set<int> my_set = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_TRUE(my_set.contains(1));
  EXPECT_FALSE(my_set.contains(-454));
  EXPECT_FALSE(my_set.contains(32322));
}

TEST(Testing_set, test_5) {
  s21::set<int> my_set;
  EXPECT_FALSE(my_set.contains(-454));
  EXPECT_FALSE(my_set.contains(32322));
}

TEST(Testing_set, test_6) {
  s21::set<int> my_set1;
  s21::set<int> my_set2 = {100, 200, 300};
  my_set1.emplace(1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9);
  my_set1.swap(my_set2);

  for (int i = 1; i < 10; i++) {
    EXPECT_TRUE(my_set2.contains(i));
  }
  EXPECT_TRUE(my_set1.contains(100));
  EXPECT_TRUE(my_set1.contains(200));
  EXPECT_TRUE(my_set1.contains(300));
}

TEST(Testing_set, test_7) {
  s21::set<int> my_set;
  for (int i = 0; i < 10000; i++) {
    my_set.insert(i);
  }
  auto it = my_set.begin();
  for (int i = 0; i < 6793; i++) {
    ++it;
  }
  my_set.erase(it);
  EXPECT_TRUE(my_set.contains(6794));
}

TEST(Testing_set, test_8) {
  s21::set<int> my_set;
  for (int i = 0; i < 10000; i++) {
    my_set.insert(i);
  }
  auto it = my_set.find(674);
  EXPECT_EQ(*it, 674);
}

TEST(Testing_set, test_9) {
  s21::set<int> my_set1;
  s21::set<int> my_set2;
  for (int i = 0; i < 10; i++) {
    my_set1.insert(i);
  }
  for (int i = 5; i < 15; i++) {
    my_set2.insert(i);
  }
  my_set1.merge(my_set2);
  for (int i = 0; i < 15; i++) {
    EXPECT_TRUE(my_set1.contains(i));
  }
  for (int i = 5; i < 10; i++) {
    EXPECT_TRUE(my_set2.contains(i));
  }
  EXPECT_EQ(my_set1.size(), 15);
  EXPECT_EQ(my_set2.size(), 5);
}

TEST(Testing_set, test_10) {
  s21::set<int> my_set = {1, 2};
  auto it = my_set.begin();
  ++it;
  my_set.erase(it);
  EXPECT_EQ(my_set.size(), 1);
}

TEST(Testing_set, test_11) {
  s21::set<int> my_set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int i = 1;
  for (auto it = my_set.begin(); it != my_set.end(); ++it, i++) {
    EXPECT_EQ(*it, i);
  }
}

TEST(Testing_set, test_12) {
  s21::set<int> my_set;
  for (int i = 0; i < 10000; i++) {
    my_set.insert(i);
  }
  auto it = my_set.end();
  for (; it != my_set.begin(); --it) {
    // my_set.erase(it);
  }
}

// Memory leak here
TEST(Testing_multiset, test_1) {
  s21::multiset<int> my_set = {1, 2, 3, 4, 5, 6, 2, 2, 2, 4, 5};
  EXPECT_FALSE(my_set.empty());
}

TEST(Testing_multiset, test_2) {
  s21::multiset<int> my_set;
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  my_set.insert(3);
  EXPECT_EQ(my_set.size(), 10);
  EXPECT_FALSE(my_set.empty());
}

TEST(Testing_multiset, test_3) {
  s21::multiset<int> my_set = {1, 2, 3, 4, 5};
  my_set.clear();
  EXPECT_TRUE(my_set.empty());
}

TEST(Testing_multiset, test_4) {
  s21::multiset<int> my_set = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_TRUE(my_set.contains(1));
  EXPECT_FALSE(my_set.contains(-454));
  EXPECT_FALSE(my_set.contains(32322));
}

TEST(Testing_multiset, test_5) {
  s21::multiset<int> my_set;
  EXPECT_FALSE(my_set.contains(-454));
  EXPECT_FALSE(my_set.contains(32322));
}

TEST(Testing_multiset, test_6) {
  s21::multiset<int> my_set1;
  s21::multiset<int> my_set2 = {100, 200, 300};
  my_set1.emplace(1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9);
  my_set1.swap(my_set2);

  for (int i = 1; i < 10; i++) {
    EXPECT_TRUE(my_set2.contains(i));
  }
  EXPECT_TRUE(my_set1.contains(100));
  EXPECT_TRUE(my_set1.contains(200));
  EXPECT_TRUE(my_set1.contains(300));
}

TEST(Testing_multiset, test_7) {
  s21::multiset<int> my_set;
  for (int i = 0; i < 10000; i++) {
    my_set.insert(i);
  }
  auto it = my_set.begin();
  for (int i = 0; i < 6793; i++) {
    ++it;
  }
  my_set.erase(it);
  EXPECT_TRUE(my_set.contains(6794));
}

TEST(Testing_multiset, test_8) {
  s21::multiset<int> my_set;
  for (int i = 0; i < 10000; i++) {
    my_set.insert(i);
  }
  auto it = my_set.find(674);
  EXPECT_EQ(*it, 674);
}

TEST(Testing_multiset, test_9) {
  s21::multiset<int> my_set1;
  s21::multiset<int> my_set2;
  for (int i = 0; i < 10; i++) {
    my_set1.insert(i);
  }
  for (int i = 5; i < 15; i++) {
    my_set2.insert(i);
  }
  my_set1.merge(my_set2);
  for (int i = 0; i < 15; i++) {
    EXPECT_TRUE(my_set1.contains(i));
  }
  for (int i = 5; i < 10; i++) {
    EXPECT_TRUE(my_set2.contains(i));
  }
  EXPECT_EQ(my_set1.size(), 15);
  EXPECT_EQ(my_set2.size(), 5);
}

TEST(Testing_multiset, test_10) {
  s21::multiset<int> my_set = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(my_set.count(1), 1);
}

TEST(Testing_multiset, test_11) {
  s21::multiset<int> my_set = {1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(my_set.count(1), 5);
}

TEST(Testing_multiset, test_12) {
  s21::multiset<int> my_set = {0, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7};
  auto p = my_set.equal_range(1);
  auto it1 = p.first;
  auto it2 = p.second;
  EXPECT_EQ(*it1, 1);
  EXPECT_EQ(*it2, 2);
}

TEST(Testing_multiset, test_13) {
  s21::multiset<int> my_set = {0, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7};
  auto it = my_set.lower_bound(1);
  EXPECT_EQ(*it, 1);
}

TEST(Testing_multiset, test_14) {
  s21::multiset<int> my_set = {0, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7};
  auto it = my_set.upper_bound(1);
  EXPECT_EQ(*it, 2);
}

TEST(Testing_array, test_1) {
  s21::array<int, 5> my_array = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_array[0], 1);
  EXPECT_EQ(my_array[1], 2);
  EXPECT_EQ(my_array[2], 3);
  EXPECT_EQ(my_array[3], 4);
  EXPECT_EQ(my_array[4], 5);
}

TEST(Testing_array, test_2) {
  s21::array<int, 3> my_array = {1, 2, 3};
  EXPECT_EQ(my_array.at(0), 1);
}

TEST(Testing_array, test_3) {
  s21::array<int, 6> my_array = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(my_array.front(), 1);
  EXPECT_EQ(my_array.back(), 6);
}

TEST(Testing_array, test_4) {
  s21::array<int, 6> my_array1 = {1, 2, 3, 4, 5, 6};
  s21::array<int, 6> my_array2 = {7, 8, 9, 10, 11, 12};
  my_array1.swap(my_array2);

  for (int i = 1; i < 7; i++) {
    EXPECT_EQ(my_array2[i - 1], i);
  }

  for (int i = 7; i < 13; i++) {
    EXPECT_EQ(my_array1[i - 7], i);
  }
}

TEST(Testing_array, test_5) {
  s21::array<int, 6> my_array = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(my_array.max_size(), 6);
}

TEST(Testing_array, test_6) {
  s21::array<int, 6> my_array1 = {1, 2, 3, 4, 5, 6};
  my_array1.fill(100);
  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(my_array1[i], 100);
  }
}

TEST(Testing_array, test_7) {
  s21::array<int, 6> my_array = {1, 2, 3, 4, 5, 6};
  int* data = my_array.data();
  EXPECT_EQ(data, my_array.data());
}

TEST(Testing_array, test_8) {
  s21::array<int, 6> my_array = {1, 2, 3, 4, 5, 6};
  EXPECT_THROW(my_array.at(10000), std::out_of_range);
}

TEST(Testing_array, test_9) {
  try {
    s21::array<int, 3> my_array = {1, 2, 3, 4, 5, 6};
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(1, 1);
  }
}

TEST(Testing_array, test_10) {
  s21::array<int, 6> my_array = {1, 2, 3, 4, 5, 6};
  int i = 1;
  for (s21::array<int, 6>::iterator it = my_array.begin(); it != my_array.end();
       ++it, i++) {
    EXPECT_EQ(*it, i);
  }
}

TEST(Testing_array, test_11) {
  s21::array<int, 6> my_array1 = {1, 2, 3, 4, 5, 6};
  s21::array<int, 6> my_array2 = std::move(my_array1);
  int i = 1;
  for (s21::array<int, 6>::iterator it = my_array2.begin();
       it != my_array2.end(); ++it, i++) {
    EXPECT_EQ(*it, i);
  }
  EXPECT_TRUE(my_array1.empty());
}

TEST(Testing_array, test_12) {
  s21::array<int, 6> my_array1 = {1, 2, 3, 4, 5, 6};
  my_array1 = std::move(my_array1);
  int i = 1;
  for (s21::array<int, 6>::iterator it = my_array1.begin();
       it != my_array1.end(); ++it, i++) {
    EXPECT_EQ(*it, i);
  }
  EXPECT_FALSE(my_array1.empty());
}

TEST(Testing_array, test_13) {
  s21::array<int, 5> my_array0;
  s21::array<int, 5> my_array1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> my_array2(my_array1);
  int i = 1;
  for (s21::array<int, 6>::iterator it = my_array2.begin();
       it != my_array2.end(); ++it, i++) {
    EXPECT_EQ(*it, i);
  }
  EXPECT_FALSE(my_array2.empty());
}

TEST(Testing_pair, test_1) {
  s21::pair<int, int> p1 = {1, 2};
  s21::pair<int, int> p2 = {2, 2};
  EXPECT_TRUE(p1 != p2);
}

TEST(Testing_pair, test_2) {
  s21::pair<int, int> p1 = {1, 2};
  s21::pair<int, int> p2 = {2, 2};
  EXPECT_TRUE(p1 <= p2);
}

TEST(Testing_pair, test_3) {
  s21::pair<int, int> p1 = {1, 2};
  s21::pair<int, int> p2 = std::move(p1);
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);
}

TEST(Testing_pair, test_4) {
  s21::pair<int, int> p1 = {1, 2};
  p1 = std::move(p1);
  EXPECT_EQ(p1.first, 1);
  EXPECT_EQ(p1.second, 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
