#define CATCH_CONFIG_MAIN

#pragma once

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

    void Print()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            std::cout << current->value << " "; 
            current = current->next;
        }
        std::cout << std::endl;
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

    List list;

    TEST_CASE("test list", "[list.Push, list.Pop]") {

        for (auto i = 1; i <= 10; ++i) {
            list.PushBack(i);
        }
        CHECK(list.Size() == 10);
        for (auto i = 11; i <= 20; ++i) {
            list.PushFront(i);
        }

        list.Print();
        CHECK(list.Size() == 20);

        for (auto i = 1; i <= 3; ++i) {
            list.PopBack();
        }
        for (auto i = 1; i <= 3; ++i) {
            list.PopFront();
        }
        list.Print();
        CHECK(list.Size() == 14);

        list.Clear();
        CHECK(list.Empty() == 1);

        REQUIRE_THROWS(list.PopBack());
        REQUIRE_THROWS(list.PopFront());

    }

