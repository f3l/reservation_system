#ifndef APPLICATION_DEFINED
#define APPLICATION_DEFINED

class application
{
private:
	int m_running;
public:
	application();
	void run();
	void print_menu();
	void end_program();
};

#endif