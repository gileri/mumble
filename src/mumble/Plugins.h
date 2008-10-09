/* Copyright (C) 2005-2008, Thorvald Natvig <thorvald@natvig.com>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   - Neither the name of the Mumble Developers nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _PLUGINS_H
#define _PLUGINS_H

#include "ConfigDialog.h"
#include "ui_Plugins.h"

struct PluginInfo;

class PluginConfig : public ConfigWidget, public Ui::PluginConfig {
	private:
		Q_OBJECT
		Q_DISABLE_COPY(PluginConfig)
	protected:
		void refillPluginList();
		QHash<QListWidgetItem *, PluginInfo *> qhInfos;
	public:
		PluginConfig(Settings &st);
		virtual QString title() const;
		virtual QIcon icon() const;
	public slots:
		void save() const;
		void load(const Settings &r);
		bool expert(bool);
		void on_qpbConfig_clicked();
		void on_qpbAbout_clicked();
		void on_qpbReload_clicked();
};

class Plugins : public QObject {
		friend class PluginConfig;
	private:
		Q_OBJECT
		Q_DISABLE_COPY(Plugins)
	protected:
		QMutex qmPlugins;
		QList<PluginInfo *> qlPlugins;
		PluginInfo *locked;
		PluginInfo *prevlocked;
	public:
		bool bValid;
		bool bUnlink;
		float fPosition[3], fFront[3], fTop[3];

		Plugins(QObject *p = NULL);
	public slots:
		void on_Timer_timeout();
		void rescanPlugins();
		bool fetch();
};

#else
class Log;
#endif
