// Copyright (c) 2019-2020 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MASTERNODESWIDGET_H
#define MASTERNODESWIDGET_H

#include "qt/spark/pwidget.h"
#include "qt/spark/furabstractlistitemdelegate.h"
#include "qt/spark/mnmodel.h"
#include "qt/spark/tooltipmenu.h"
#include "walletmodel.h"

#include <atomic>

#include <QTimer>
#include <QWidget>

class SPARKGUI;

namespace Ui {
class MasterNodesWidget;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class MasterNodesWidget : public PWidget
{
    Q_OBJECT

public:

    explicit MasterNodesWidget(SPARKGUI *parent = nullptr);
    ~MasterNodesWidget();

    void loadWalletModel() override;

    void run(int type) override;
    void onError(QString error, int type) override;

    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private Q_SLOTS:
    void onCreateMNClicked();
    void onStartAllClicked(int type);
    void changeTheme(bool isLightTheme, QString &theme) override;
    void onMNClicked(const QModelIndex &index);
    void onEditMNClicked();
    void onDeleteMNClicked();
    void onInfoMNClicked();
    void updateListState();
    void updateModelAndInform(const QString& informText);

private:
    Ui::MasterNodesWidget *ui;
    FurAbstractListItemDelegate *delegate;
    MNModel *mnModel = nullptr;
    TooltipMenu* menu = nullptr;
    QModelIndex index;
    QTimer *timer = nullptr;

    std::atomic<bool> isLoading;

    bool checkMNsNetwork();
    void startAlias(const QString& strAlias);
    bool startAll(QString& failedMN, bool onlyMissing);
    bool startMN(const CMasternodeConfig::CMasternodeEntry& mne, std::string& strError);
};

#endif // MASTERNODESWIDGET_H
