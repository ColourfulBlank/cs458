#Assignment 1 CS 454 
##Wang Weicheng
###w257wang 20487825
####Question 1
If a client and a server are placed far apart, we may see network latency dominating overall performance. How can we tackle this problem?

We can add more servers, that server places in different locations that one server can locate near the client.  Or, we can try to do something on the client side, for example, let client do some other works while waiting for the reply.

####Question 2
Are there advantages of using synchronous RPC over asynchronous RPC? If so, describe them. If not, provide an explanation of why not. 

Synchronous RPC will wait for result back from the server, but asynchronous RPC will keep doing something else after it makes sure server get it’s request. I am thinking If server can response the client right away after it received the request, and send back immediately. client side will be wasting time doing content switch, since it won’t actually doing other works. If client make this kind of request very often, it may be have to do a lot of content switch.

####Question 3
A single data request message is sent by a client to a single application server. The application server uses the content of this message to create a pair of request messages, one for each specific database at the backend tier. Responses to these messages are returned from the two databases to the application server and are forwarded on by the application server as two separate responses to the client. Explain the transparency implications of this design decision. 
    

If one of database servers downed, client still can get the response. and client won’t need to worry about it, because it can get the result it needs.
client won’t need to send multiple requests to the database servers to get the response.
client won't need to know how to communicate with database servers, application server will response to translate the request.

####Question 4
Compare, and discuss briefly, connectionless (UDP) and connection-oriented (TCP) communication for the implementation of each of the following application-level or presentation-level protocols
1.virtual terminal access (for example, Telnet)           
    __TCP__ can keep two ends connected and keep a bandwidth for the communication, while UDP will not provide these, if we use UDP, we need to implement those feature at application layer. but with UDP we may have a better communication speed, since UDP doesn’t have congestion control.

2.file transfer (for example, FTP)
    __TCP__ can keep two ends connected and keep state for the communication, while UDP will not provide these, if we use UDP, we need to implement those feature at application layer and also need to make sure recovery from data loss. but with UDP we may have a better communication speed, since UDP doesn’t have congestion control.
3.user location (for example, rwho, finger)
    __UDP__ it’s good enough for this I think. since we only need to transfer a little bit of data, it is wasteful to spend time set up a communication path. But if the there is a lot of data need transfer TCP will be a better option, because it will handle data loss.
4.information browsing (for example, HTTP);
    TCP, since we don't want to lost data when transfer.
5.remote procedure call
    __TCP__, we need to keep track of state and a consistent tunnel for remote function calls.
####Question 5    
Assume n computers are interconnected and the availability of each computer is needed to maintain a distributed service, and each of these computers has a probability p (0 ≤ p ≤ 1) of failing at any time.

1. What is the probability ps that the service will not be available at any time, assuming that no other components in the distributed system will fail? Express ps as a mathematical function of n and p?  
Ps = 1 - (1 - p) ^ n
2. Based on your answer for part (1), what is the probability ps when computing is not distributed, i.e., for the case where n = 1?  
Ps = p
3. Based on your answer for part (1), use p = 0.2 and n = 3 to compute probability ps. How does this probability compare with the failure probability if the same computing is performed on only one computer?   
On three computers Ps = 0.488  
On ont computers Ps = 0.2  
failure probability goes higher
4. Now assume that the service requires only one of the three computers (not each one of them), with the other two computers serving as backups (that is, each of the three computers, on its own, is capable of providing the service). What is the probability that the service will not be available at anytime, assuming that no other components in the distributed system will fail? How does the failure probability of this system compare with the failure probability if the same computing is performed on one computer only?   
ps =  p^n = 0.2 ^ 3 = 0.008 







