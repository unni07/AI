Student Name: Unnikrishnan Nair

Project Name: StateMachine

What I implemented: 
I implemented a zombie demo:
There are 2 types of zombie
	- Feeble Zombie
	- Zombie
Feeble Zombie:
Feeble Zombie is scared of human beinga and it flees when a human is nearning them. On contact with a human feeble zombie dies (is marked for death)
A death of a feeble zombie trigges a global message where all the remaining feeble zombie runs towards the closest strong zombie.

Strong Zombie:
Strong Zombie or just Zombie can conver human being to a zombie. It protects feeble zombie

Human:
Human is wandering randomly and when it detects a feeble zombie in a range it chase and attacks it.It is scared of strong zombie and will flee if one is in the vicinity.

Directions (if needed):
Execute and and its simple. If the humans are not going near feeble or strong zombie left click near them and it will follow.

My experience working on this project:
It was a fun project. Helped improve my understanding of state machine.

Hours spent:
I spent 2-3 hours reading the PPT and source code. Then realized the most important files to refer is World.cpp and Example.cpp. From there it was a smooth sail.
I spent 3-4 hours in implementation and debugging

5 features (include which file and line number):
Substates:
File:Zombie.cpp
line: 79
This is used to toggle between 2 colors: red and green. This simulates the effect of human to zombie conversion.

GlobalMessageResponse:
File: FeebleZombie.cpp
line: 29
When a feeble zombie dies it sends out a message, MSG_Dead.This message is only acceptable for other feeble zombies. Feeble zombie will find the closest strong zombie to hide.

ReplaceStateMachine:
File: Human.cpp
line: 123
When human gets converted to zombie the state machine is replaced.

Data passed in Message:
File: Human.cpp
line 122
when azombie locks down a human it will hunt it down. When zombie is converted a message with its id is passed. This confirmed by zombie at line 88. Then zombie change state to wander.

MarkForDeletion:
File: FeebleZombie.cpp
line: 54
When human is near a feeble zombie it dies. This is triggered by marking the feeble zombie for deletion.

OnPeridicTimeInState:
File: FeebleZombie.cpp
line: 81
when human and a zombie guy is in touch with each other, human changes color.

Extra credit: