/*
	Actionaz
	Copyright (C) 2008-2010 Jonathan Mercier-Ganady

	Actionaz is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actionaz is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#ifndef KILLPROCESSINSTANCE_H
#define KILLPROCESSINSTANCE_H

#include "actioninstanceexecutionhelper.h"
#include "actioninstance.h"
#include "script.h"
#include "crossplatform.h"

namespace Actions
{
	class KillProcessInstance : public ActionTools::ActionInstance
	{
		Q_OBJECT
		Q_ENUMS(KillMode)

	public:
		enum KillMode
		{
			Graceful = ActionTools::CrossPlatform::Graceful,
			Forceful = ActionTools::CrossPlatform::Forceful,
			GracefulThenForceful = ActionTools::CrossPlatform::GracefulThenForceful
		};

		KillProcessInstance(const ActionTools::ActionDefinition *definition, QObject *parent = 0)
			: ActionTools::ActionInstance(definition, parent)												{}

		static ActionTools::StringListPair killModes;

		void startExecution()
		{
			ActionTools::ActionInstanceExecutionHelper actionInstanceExecutionHelper(this, script(), scriptEngine());
			int processId;

			if(!actionInstanceExecutionHelper.evaluateInteger(processId, "processId"))
				return;

			if(processId != 0)
				ActionTools::CrossPlatform::killProcess(processId, ActionTools::CrossPlatform::GracefulThenForceful, 100);

			emit executionEnded();
		}

	public slots:
		bool killProcess(int processId, KillMode killMode = GracefulThenForceful, int timeout = 1000)
		{
			return ActionTools::CrossPlatform::killProcess(processId, static_cast<ActionTools::CrossPlatform::KillMode>(killMode), timeout);
		}

	private:
		Q_DISABLE_COPY(KillProcessInstance)
	};
}

#endif // KILLPROCESSINSTANCE_H