#pragma once

#include <list>
#include <unordered_map>

#include <base/signal.h>
#include <dom0/task_manager_session.h>
#include <os/attached_ram_dataspace.h>
#include <os/server.h>
#include <root/component.h>
#include <timer_session/connection.h>
#include <util/string.h>

#include "task.h"

struct Task_manager_session_component : Genode::Rpc_object<Task_manager_session>
{
public:
	Task_manager_session_component(Server::Entrypoint& ep);
	virtual ~Task_manager_session_component();

	// Create tasks in idle state from XML description.
	void add_tasks(Genode::Ram_dataspace_capability xml_ds_cap);

	// Allocate and return a capability of a new dataspace to be used for a task binary.
	Genode::Ram_dataspace_capability binary_ds(Genode::Ram_dataspace_capability name_ds_cap, size_t size);

	// Destruct all tasks.
	void clear_tasks();

	// Start idle tasks.
	void start();

	// Stop all tasks.
	void stop();

	// Pause all tasks.
	void pause();

	// Resume all tasks.
	void resume();

	// Get profiling data as an XML file.
	Genode::Ram_dataspace_capability profile_data();

protected:
	Server::Entrypoint& _ep;
	Task::Shared_data _shared;
	Genode::Cap_connection _cap;

	size_t _quota;

	Genode::Attached_ram_dataspace _profile_data;

	static Genode::Number_of_bytes _trace_quota();
	static Genode::Number_of_bytes _trace_buf_size();
	static Genode::Number_of_bytes _profile_ds_size();
};

struct Task_manager_root_component : Genode::Root_component<Task_manager_session_component>
{
public:
	Task_manager_root_component(Server::Entrypoint* ep, Genode::Allocator *allocator) :
		Genode::Root_component<Task_manager_session_component>(&ep->rpc_ep(), allocator),
		_ep(*ep)
	{
		PDBG("Creating root component.");
	}

protected:
	Server::Entrypoint& _ep;

	Task_manager_session_component* _create_session(const char *args)
	{
		PDBG("Creating Task Manager session.");
		return new (md_alloc()) Task_manager_session_component(_ep);
	}
};
