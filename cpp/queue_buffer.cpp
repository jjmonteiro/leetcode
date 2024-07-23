
#include <iostream>
#include <vector>
using namespace std;

#define LOG(x) std::cout << x << std::endl;
#undef POINTER_QUEUE


class myobj
{
public:
    int a,b,c;
};

#ifdef POINTER_QUEUE
bool dequeue(myobj* new_data)
{
    bool result = false;

    if (rand() % 2) // fails 1/3 of times
    {
        LOG("====");
        LOG("deq: " << new_data->a);
        LOG("deq: " << new_data->b);
        LOG("deq: " << new_data->c);
        result = true;
        if (new_data != nullptr)
        delete new_data;
    }

    return result;
}
void enqueue(myobj* new_data)
{
    uint8_t cn_LOCK_BUFFER_SIZE = 1;
    uint8_t cn_DELIVERY_ATTEMPTS = 5;
    static std::vector<myobj*> buffer_data;

    if (buffer_data.size() < cn_LOCK_BUFFER_SIZE)
    {
        buffer_data.push_back(new_data);
    }
    else
    {
        if (new_data != nullptr)
        delete new_data;       
        LOG("PACKET LOST!");
    }

    for (uint8_t att = 0; ((att < cn_DELIVERY_ATTEMPTS) && buffer_data.size()); att++)
    {
        if (dequeue(buffer_data.front()))
        {
            buffer_data.erase(buffer_data.begin());
        }
    }
}
#endif
#ifndef POINTER_QUEUE
bool dequeue(myobj& new_data)
{
    bool result = false;

    if (rand() % 2)
    {
        LOG("====");
        LOG("deq: " << new_data.a);
        LOG("deq: " << new_data.b);
        LOG("deq: " << new_data.c);
        result = true;
    }

    return result;
}
void enqueue(myobj& new_data)
{
    uint8_t cn_LOCK_BUFFER_SIZE = 1;
    uint8_t cn_DELIVERY_ATTEMPTS = 5;
    static std::vector<myobj> buffer_data;

    if (buffer_data.size() < cn_LOCK_BUFFER_SIZE)
    {
        buffer_data.push_back(new_data);
    }
    else
    {
        LOG("PACKET LOST!");
    }

    for (uint8_t att = 0; ((att < cn_DELIVERY_ATTEMPTS) && buffer_data.size()); att++)
    {
        if (dequeue(buffer_data.front()))
        {
            buffer_data.erase(buffer_data.begin());
        }
    }
}
#endif

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#ifdef POINTER_QUEUE
    for (int idx = 0; idx < 100; idx++)
    {
        myobj* data = new myobj;
        data->a = rand() % 100;
        data->b = rand() % 100;
        data->c = rand() % 100;
        LOG("====");
        LOG("enq: " << data->a);
        LOG("enq: " << data->b);
        LOG("enq: " << data->c);
        enqueue(data);
    }
#endif
#ifndef POINTER_QUEUE
    for (int idx = 0; idx < 100; idx++)
    {
        myobj data;
        data.a = rand() % 100;
        data.b = rand() % 100;
        data.c = rand() % 100;
        LOG("====");
        LOG("enq: " << data.a);
        LOG("enq: " << data.b);
        LOG("enq: " << data.c);
        enqueue(data);
    }
#endif
    return(0);
}

