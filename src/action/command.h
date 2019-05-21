class Command
{
public:
	virtual bool Execute() = 0; //Actually executes the user's request
	virtual bool Unexecute() = 0; //Undoes the operation performed by the Execute method
	virtual ~Command() { }
};

class CommandManager
{
	//undo stack
	//redo stack
	/*
	Everytime you need to do a command, you construct a command
	object and call CommandManager.DoCommand method, passing the
	object as the parameter.  Call CommandManager's Undo and Redo 
	methods to undo and redo
	https://www.codeproject.com/Articles/2500/A-Basic-Undo-Redo-Framework-For-C
	*/
};