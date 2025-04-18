# SoC_HW1_C110112124
# FPGA LED 跑馬燈專案

## 專案概述

本專案使用 FPGA 實現 LED 跑馬燈效果。系統主要包含兩個部分：

## 功能

- **LED 跑馬燈：** LED 按順序依次亮起，呈現跑馬燈效果。
- **速度控制：** 按下按鈕可以加速跑馬燈的效果。
- **反向控制：** 使用開關可以反轉 LED 顯示的順序。

## 硬體

- **開發板：** EGO-XZ7（Zynq-7000 SoC，型號：XC7Z020CLG484-1）
- **處理器：** ARM Cortex-A9
- **LED：** 展示跑馬燈效果
- **按鈕：** 用於控制跑馬燈的速度
- **開關：** 用於反轉 LED 顯示順序

## 軟體工具

- **Xilinx Vivado 2018：** 用於硬體設計與綜合。
- **Xilinx SDK：** 用於開發軟體並控制 PS。

## Block 設計
![HW1_block_design](https://github.com/user-attachments/assets/a00aa4a4-4aa7-46e9-87b9-e81812e7b0df)



## 影片

以下是展示 FPGA LED 跑馬燈功能的影片：


https://github.com/user-attachments/assets/9a60ccbf-8521-440a-8b47-a3a73cae1e72






## 工作原理

- PS 根據c程式生成跑馬燈信號。
- 包含按住按鈕會通過調整信號時間來加速跑馬燈效果。
- RTL 設計接收跑馬燈信號並輸出 LED 的顯示。
- 包含開關可以讓使用者反轉 LED 亮滅。
