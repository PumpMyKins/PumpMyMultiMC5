/* Copyright 2013-2018 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <QWidget>
#include <QTreeView>
#include <QTextBrowser>

#include "pages/BasePage.h"
#include <MultiMC.h>
#include "tasks/Task.h"
#include "modplatform/pmp/PackHelpers.h"
#include "modplatform/pmp/PmpPackFetchTask.h"
#include "QObjectPtr.h"

namespace Ui
{
class PMPacksPage;
}

class PmpListModel;
class PmpFilterModel;
class NewInstanceDialog;

class PMPacksPage : public QWidget, public BasePage
{
    Q_OBJECT

public:
    explicit PMPacksPage(NewInstanceDialog * dialog, QWidget *parent = 0);
    virtual ~PMPacksPage();
    QString displayName() const override
    {
        return tr("PumpMyPacks");
    }
    QIcon icon() const override
    {
        return MMC->getThemedIcon("pmk");
    }
    QString id() const override
    {
        return "pmk";
    }
    QString helpPage() const override
    {
        return "FTB-platform";
    }
    bool shouldDisplay() const override;
    void openedImpl() override;

private:
    void suggestCurrent();
    void onPackSelectionChanged(PmpModpack *pack = nullptr);

private slots:
    void pmpPackDataDownloadSuccessfully(PmpModpackList publicPacks, PmpModpackList betaPacks);
    void pmpPackDataDownloadFailed(QString reason);

    void onSortingSelectionChanged(QString data);
    void onVersionSelectionItemChanged(QString data);

    void onPublicPackSelectionChanged(QModelIndex first, QModelIndex second);
    void onBetaPackSelectionChanged(QModelIndex first, QModelIndex second);

    void onTabChanged(int tab);


private:
    PmpFilterModel* currentModel = nullptr;
    QTreeView* currentList = nullptr;
    QTextBrowser* currentModpackInfo = nullptr;

    bool initialized = false;
    PmpModpack selected;
    QString selectedVersion;

    PmpListModel* publicListModel = nullptr;
    PmpFilterModel* publicFilterModel = nullptr;

    PmpListModel *betaListModel = nullptr;
    PmpFilterModel *betaFilterModel = nullptr;

    unique_qobject_ptr<PmpPackFetchTask> pmpFetchTask;

    NewInstanceDialog* dialog = nullptr;

    Ui::PMPacksPage *ui = nullptr;
};
