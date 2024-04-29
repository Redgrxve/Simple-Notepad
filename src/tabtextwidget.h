#ifndef TABTEXTWIDGET_H
#define TABTEXTWIDGET_H

#include <QTabWidget>

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
    int addTabWithButton();
    TextFileEditWidget* getCurrentTextEdit();
    void setCurrentTabText(const QString &text);
    QString getCurrentTabText() const;
    bool isCurrentTabUnsaved();

private:
    Ui::TabTextWidget *ui;
    int newTabNumber = 0;

    void readFile(const QString& filePath);

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
    void onTextSaved(const QString& fileName);
    void onTextUnsaved();
};

#endif // TABTEXTWIDGET_H
