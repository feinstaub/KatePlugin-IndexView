/*   This file is part of KatePlugin-IndexView
 *
 *   IndexView Class
 *   Copyright (C) 2018 loh.tar@googlemail.com
 *
 *   Based on
 *   plugin_katesymbolviewer
 *   Copyright (C) 2014 Kåre Särs <kare.sars@iki.fi>
 *   Copyright (C) 2003 Massimo Callegari <massimocallegari@yahoo.it>
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Library General Public
 *   License as published by the Free Software Foundation; either
 *   version 2 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Library General Public License for more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifndef INDEX_VIEW_H
#define INDEX_VIEW_H

#include <QPointer>
#include <QTimer>
#include <QTreeWidget>

#include <KTextEditor/MainWindow>
#include <KTextEditor/SessionConfigInterface>
#include <KTextEditor/View>
#include <KXMLGUIClient>

class KatePluginIndexView;
class FilterBox;
class Parser;

class IndexView : public QObject
                , public KXMLGUIClient
                , public KTextEditor::SessionConfigInterface

{
    Q_OBJECT
    Q_INTERFACES(KTextEditor::SessionConfigInterface)

    friend class KatePluginIndexView;
    friend class FilterBox;
    friend class Parser;

public:
    IndexView(KatePluginIndexView *plugin, KTextEditor::MainWindow *mw);
    ~IndexView() override;

    void readSessionConfig(const KConfigGroup &config) override;
    void writeSessionConfig(KConfigGroup &config) override;

public Q_SLOTS:
    void loadViewSettings();
    void saveViewSettings();
    void docChanged();
    bool docModeChanged();
    void docEdited();
    void docSelectionChanged();
    void docCursorPositionChanged();
    void updateCurrTreeItem();
    void filterTree();
    void showContextMenu(const QPoint&);
    void parseDocument();
    void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void itemClicked(QTreeWidgetItem *);

// protected:
    // Disabled because I can't see any effect
//     bool eventFilter(QObject *obj, QEvent *ev) override;

private:
    int  filterBoxPosition();
    void updateFilterBoxPosition(int pos);
    void restoreTree();

    KTextEditor::MainWindow    *m_mainWindow;
    QPointer<Parser>            m_parser;

    QString                     m_docType;
    QWidget                    *m_toolview;
    QTreeWidget                *m_indexTree;
    QList<QTreeWidgetItem *>    m_indexList;

    QAction                    *m_viewSort;
    QAction                    *m_viewTree;
    QAction                    *m_viewExpanded;

    QTimer                      m_parseDelayTimer;
    QTimer                      m_updateCurrItemDelayTimer;
    int                         m_currentLineNumber;
    FilterBox                  *m_filterBox;
    QTimer                      m_filterDelayTimer;
    bool                        m_filtered;

    bool                        m_cozyClickExpand;
    bool                        m_currentItemChanged;
    int                         m_parseDelay;

};

#endif

// kate: space-indent on; indent-width 4; replace-tabs on;
