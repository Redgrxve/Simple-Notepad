#ifndef TABTEXTWIDGET_H
#define TABTEXTWIDGET_H

#include <QTabWidget>
#include <QStack>

class TabButtonWidget;
class TextFileEditWidget;

namespace Ui {
class TabTextWidget;
}

class TabTextWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabTextWidget(QWidget *parent = nullptr);
    ~TabTextWidget();

    void openFileInNewTab(const QString &filePath);
    void openFileInCurrentTab(const QString &filePath);
    void saveCurrentTab(const QString &filePath);
    void saveTab(int tabIndex, const QString &filePath);
    void saveAllUnsavedTabs();
    int addTabWithButton();
    TextFileEditWidget* getCurrentTextEdit();
    TextFileEditWidget* getTextEdit(int tabIndex);
    void setCurrentTabText(const QString &text);
    QString getCurrentTabText() const;
    bool isCurrentTabUnsaved();

private:
    Ui::TabTextWidget *ui;
    int newTabNumber = 0;
    QMap<int, int> unsavedTabsIndexes;

    void readFile(const QString& filePath);
    void execSaveDialog(int unsavedTabIndex);

signals:
    void tabAdded(int index);
    void tabClosed(int index);
    void tabSaved();
    void tabUnsaved();
    void tabMoved(int from, int to);

private slots:
    void onCloseTabClicked(const TabButtonWidget* sender);
    void onSaveDialogAccepted(int tabIndex);
    void onSaveDialogRejected(int tabIndex);
    void onTextReaded(const QString& fileName);
    void onTextSaved(const QString& fileName);
    void onTextUnsaved();
    void onUndoAvailable(bool available);
};

#endif // TABTEXTWIDGET_H
