#pragma once

#include "DebugLogger.h"

/**
 * Class to access global logger.
 * */
class StaticLogger 
{
    public:
        /// <summary>
        /// Singleton instance for the debug logger.
        /// </summary>
        static DebugLogger instance;

	private:
        /// <summary>
        /// Static constructor.
        /// </summary>
        class constructor 
        {
            public:
                constructor() 
                {
                    #ifdef _DEBUG
                        instance.setLevel(Level::LEVEL_TRACE);
                    #else
                        instance.setLevel(Level::LEVEL_ERROR);
                    #endif
                }
        };

        friend class constructor;
        static constructor staticConstructor;
};


