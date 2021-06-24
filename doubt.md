hi people , 
I would like to hear your opinions and the ways you know or thought for implementing state design pattern in c
reference link: https://gameprogrammingpatterns.com/state.html

i was just interested in how we can do it in c.

In the example mentioned in the above link, Heroine is an entity that can enter many states.
I am not going to discuss the pattern again as it might make you guys feel boring so i will come straight to question.
i am not sure how to frame this in a single statement, so i will take some lines to explain it.

Handleinput() gets the input to decide on all the possible state transitions from the current state.
It makes sense to group the state transition logic into a state as the state transition is only limited to transitions
to which the heroine can go to from the current state.

In other programming languages every abstract class can have their own variables which other abstractions may or may not  have them which is really nice.
But in c, we can start defining a class by using struct.
let us say our struct has following members to it

struct state {
 void (*handleinput)(input_t input);
void (*Executestate)(void)
};

say the controls are as follows  up arrow - jump  down arrow - duck.
So lets say if the entity enters into ducking state we need to be there for 3 secs (stupid but for now lets assume like this ) but when the
entity enters into jump there it should come out instantly (again double stupid but its ok for now ). 

struct state {
int time;
 void (*handleinput)(input_t input);
void (*Executestate)(void)
};

Then if i add a variable time as follows then the variable time will be present in all the states.
Some states might need some other variables instead of time.
Then the main struct should be changed and all states will have those variables which they will not be using but just a waste of memory.

i was thinking of some way to do this in c and i only got a simple way but i am not sure if its the better way.

we can define a state specific param structs which contains state specific parameters stored which other states need not carry.
to make this work we might need to change the heroine as follows

struct state {
 void (*handleinput)(input_t input);
void (*Executestate)(state *this)
};

struct Ducking_specific_params{
 all variables we want;
};

struct jumping_specific_params{
 all variables we want;
}

and we just use them inside Executestate. but then it calls for two structs. Thing is you cant see that you are dealing with another struct
called params unless executestate is read and if we want it to be noticable then we have to create a void * like below

struct state {
void * params;
 void (*handleinput)(input_t input);
void (*Executestate)(state *this)
};

and then type cast the params into statespecificparam stuff and use it.

Do you guys have any other ways of doing it in c?






