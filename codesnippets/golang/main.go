package main

import (
	"fmt"
	"time"
)

//TimeToString 时间转换为字符串
func TimeToString(time *time.Time) string {
	return time.Format("2006-01-02 15:04:05")
}

//Float32ToString 浮点数转换为字符串
func Float32ToString(float float32) string {
	return fmt.Sprintf("%g", float)
}

//Float64ToString 浮点数转换为字符串
func Float64ToString(float float64) string {
	return fmt.Sprintf("%g", float)
}

//Int8ToString 数字转换为字符串
func Int8ToString(num int8) string {
	return fmt.Sprintf("%d", num)
}

//Int16ToString 数字转换为字符串
func Int16ToString(num int16) string {
	return fmt.Sprintf("%d", num)
}

//Int32ToString 数字转换为字符串
func Int32ToString(num int32) string {
	return fmt.Sprintf("%d", num)
}

//IntToString 数字转换为字符串
func IntToString(num int) string {
	return fmt.Sprintf("%d", num)
}

//Int64ToString 数字转换为字符串
func Int64ToString(num int64) string {
	return fmt.Sprintf("%d", num)
}

//BoolToString 布尔转换为字符串
func BoolToString(b bool) string {
	return fmt.Sprintf("%t", b)
}

//BytesToString 字节转换为字符串
func BytesToString(bytes []byte) string {
	return string(bytes)
}

//StringToBytes 字符串转换为字节数组
func StringToBytes(str string) []byte {
	return []byte(str)
}

func main() {
}
