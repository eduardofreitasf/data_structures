# Common Data Structures

The data structures implemented in this folder are:
- **Arrays**
- **Stacks**
- **Queues**

## Array

The [Array](/common/arrays/) allows the user to store simple data types, 
and provides some operations like: prepend, append and insertion, removal (pop the last element), check what element is at a given index, sorting and some others.

This implementation is **generic** and **dynamic**, when the array is full, **doubles** in size, and when it the load factor is less than 30%, the size is **reduced** to 2/3 of the original size.


## Stacks

There are two [Stack](/common/stacks/) implementations, using a **dynamic array** and a **linked list**.
The operations provided are: adding and element to top, removing the top, peeking the top and clearing the stack.

The array implementation follows the same dynamic allocation as the array, doubles the size when it's full, and reduces to 2/3 when it's less than 30%.

Both versions follow the concept of [LIFO](https://pt.wikipedia.org/wiki/LIFO)


## Queues

There are three variations of a [Queue](/common/queues/):
- Simple Queue
- Double Ended Queue
- Circular Queue

The simple [Queue](/common/queues/queue/), follows the standard concept of [FIFO](https://pt.wikipedia.org/wiki/FIFO), and there is also two versions, an array implementation and linked list implementation. The provided operations are: enqueue, dequeue, peeking the ends and clearing the queue.

The [Double Ended Queue](/common/queues/double_ended_queue/) is a Queue that allows to opperate on both ends, we are capable of adding and removing elements from the front and back of the Queue.

The [Circular Queue](/common/queues/circular_queue/) is another version of a queue, as the name indicates, the shape is as circle in which the last node of the queue is conected to the first. The upside of this implementation is that, there is no necessity for storing two pointers, since the last is linked to the first.