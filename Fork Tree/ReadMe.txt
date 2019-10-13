# Fork Tree
Operating Systems Project 1

Summary
	Fork is an operation whereby a process creates a copy of itself called the child process. It is usually a system call, implemented in the kernel. It teaks no arguments and retuns a process ID. Without fork you would have a unix system that could only run init.

Overview
	Your task is to create a simple Process Hierarchy. In this Hierarchy Process A is the parent process which has two children(B and C).
	One child(B) will have no children while the second child(C) will have two children(D and F). Child D will have one child(E) while child F will have no children.
	When a child is created, you must show its pid() and its parents pid(). When a child is destoryed, you must show its pid() its parents pid() and the number of children it has.

Sample Output:	
	Process A: Pid: 3667, Parent: 3336
	Child B: Pid: 3668, Parent: 3667
	Child B: Pid: 3668, Parent: 3667, Children: 0
	Child C: Pid: 3669, Parent: 3667
	Child D: Pid: 3670, Parent: 3669
	Child F: Pid: 3671, Parent: 3670
	Child F: Pid: 3671, Parent: 3670, Children: 0
	Child D: Pid: 3670, Parent: 3669, Children: 1
	Child E: Pid: 3672, Parent: 3669
	Child E: Pid: 3672, Parent: 3669, Children: 0
	Child C: Pid: 3669, Parent: 3667, Children: 2
	Process A: Pid: 3667, Parent: 3336, Children: 2