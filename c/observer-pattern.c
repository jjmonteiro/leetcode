#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_SUBSCRIBERS 10

typedef enum
{
  TOPIC_1,
  TOPIC_2,
  TOPIC_3
} topic_t;

typedef struct
{
  char*     myName;
  topic_t   myTopic;
} subscriber_t;

typedef struct
{
  subscriber_t* subs_list[MAX_SUBSCRIBERS];
} publisher_t;

void clientFunc(subscriber_t* subs)
{
  printf("Client %s was notified!\n", subs->myName);
}

void addClient(publisher_t* pub, subscriber_t* subs)
{
  bool success = false;

  for (int i = 0; i < MAX_SUBSCRIBERS; i++)
  {
    if (pub->subs_list[i] == NULL && !success)
    {
      pub->subs_list[i] = subs;
      printf("Client %s added.\n", subs->myName);
      success = true;
    }
  }

  if (!success)
  {
    printf("error: Failed to add client.\n");
  }
}

void removeClient(publisher_t* pub, subscriber_t* subs)
{
  bool success = false;

  for (int i = 0; i < MAX_SUBSCRIBERS; i++)
  {
    if (pub->subs_list[i] == subs && !NULL)
    {
      printf("Client %s removed.\n", subs->myName);
      pub->subs_list[i] = NULL;
      success = true;
    }
  }

  if (!success)
  {
    printf("error: Failed to remove client.\n");
  }
}

void notifyClients(publisher_t* pub, topic_t topic)
{
  bool success = false;

  for (int i = 0; i < MAX_SUBSCRIBERS; i++)
  {
    if (pub->subs_list[i] != NULL && pub->subs_list[i]->myTopic == topic)
    {
      clientFunc(pub->subs_list[i]);
      success = true;
    }
  }

  if (!success)
  {
    printf("error: No clients to notify.\n");
  }
}

int main()
{
  subscriber_t Client1  = { "Johnny", TOPIC_2 };
  subscriber_t Client2  = { "Maria",  TOPIC_1 };

  publisher_t  Subject1 = { NULL };

  addClient(&Subject1, &Client1);
  addClient(&Subject1, &Client2);

  notifyClients(&Subject1, TOPIC_3);

  removeClient(&Subject1, &Client1);

  notifyClients(&Subject1, TOPIC_1);
  notifyClients(&Subject1, TOPIC_2);
  
  addClient(&Subject1, &Client1);
}