#pragma once
#include "ClibUtil/singleton.hpp"

namespace EventSinks {
    void Install();
};

class EventSink final : 
	public clib_util::singleton::ISingleton<EventSink>,
	public RE::BSTEventSink<SKSE::CrosshairRefEvent>
{
public:
	RE::BSEventNotifyControl ProcessEvent(const SKSE::CrosshairRefEvent* a_event,
                                              RE::BSTEventSource<SKSE::CrosshairRefEvent>*) override;
};