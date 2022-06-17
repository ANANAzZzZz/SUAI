#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>

typedef int telem;    /*определение типа значений элементов массива*/
typedef telem* tstr;    /*определение типа "указатель на telem"*/
typedef tstr* tmatr;    /*определение типа "указатель на указатель на telem"*/


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_Create_clicked() {
  int spinBoxValue = ui->spinBox->value();
  int n = spinBoxValue * 2;


  ui->tableWidget->setRowCount(n);
  ui->tableWidget->setColumnCount(n);

  ui->tableWidget_2->setRowCount(n);
  ui->tableWidget_2->setColumnCount(n);
}

void MainWindow::on_AutomaticInputButton_clicked() {
  for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
      QTableWidgetItem* itm = new QTableWidgetItem(tr("%1").arg(10 * i + j));

      ui->tableWidget_2->setItem(i, j, itm);

    }
}

void MainWindow::on_sortButton_clicked() {
  int j, i, k, cItem, pItem;
  int zero;
  int temp;
  bool flag;
  int n = ui->tableWidget_2->columnCount();
  bool error = false;

  // копирование матрицы
  for (int i = 0; i < ui->tableWidget_2->rowCount(); i++) {
    if (!error) {
      for (int j = 0; j < ui->tableWidget_2->columnCount(); j++) {
        QTableWidgetItem* fItm = ui->tableWidget_2->item(i, j);

        if (fItm == nullptr || !fItm || fItm->text().isEmpty()) {
          QMessageBox::critical(this, "Ошибка", "Исходная матрица заполнена не полностью!");
          error = true;
          break;
        }

        QTableWidgetItem* sItm = new QTableWidgetItem(tr("%1").arg(fItm->text().toInt()));

        ui->tableWidget->setItem(i, j, sItm);
      }
    }
  }

  for (j = 0; j < n; j++) {
    /*начальное количество не сортированных элементов строки*/

    if (j < n / 2.) {
      k = j;
    } else {
      k = n - j - 1;
    }
    //запоминаем изначальное количество неотсортированных элементов
    zero = k + 1;
    do {
      flag = false;

      for (i = n - 1; i > n - k - 1; i--) {
        if (error) {
          break;
        }

        QTableWidgetItem* itm1 = ui->tableWidget->item(i, j);
        QTableWidgetItem* itm2 = ui->tableWidget->item(i - 1, j);

        cItem = itm1->text().toInt();
        pItem = itm2->text().toInt();

        if (cItem > pItem) {
          temp = cItem;
          cItem = pItem;
          pItem = temp;

          QTableWidgetItem* itm3 = new QTableWidgetItem(tr("%1").arg(cItem));
          QTableWidgetItem* itm4 = new QTableWidgetItem(tr("%1").arg(pItem));

          ui->tableWidget->setItem(i, j, itm3);
          ui->tableWidget->setItem(i - 1, j, itm4);

          flag = true;
        }
      }

      k--;
    } while (flag);
    for (i = 0; i < n - zero; i++) {
      if (error) {
        ui->tableWidget->clearContents();
        break;
      }
      fillMatrixZeroes(i, j);
    }

  }
}

void MainWindow::on_clearButton_clicked() {
  ui->tableWidget_2->clearContents();
  ui->tableWidget->clearContents();
}

void MainWindow::on_info_triggered() {
  QMessageBox::information(this, "Информация",
                           "Данная программа предназначена для сортировки треугольной области"
                           " матрицы методом обмена с флагом перестановки. \n"
                           "\nДля выбора размера матрицы введите в специальном поле размер n."
                           " (матрица размера 2*n) \n"
                           "\nДля ускоренного заполнения элементов матрицы создан режим автоматического"
                           " ввода, достаточно просто нажать на кнопку. \n"
                           "\nПосле выбора размера матрицы и ввода ее элементов можно нажать на кнопку"
                           " сортировки, чтобы получить результат.");
}

void MainWindow::fillMatrixZeroes(int i, int j) {
  QTableWidgetItem* itm3 = new QTableWidgetItem(tr("%1").arg(0));
  ui->tableWidget->setItem(i, j, itm3);
}
