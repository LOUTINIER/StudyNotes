# 排序

## 插入排序

确定一个序列，每次长度增加1，每轮排序都是为了保证该序列有序。

```c++
void InsertSort(int32_t *A, uint16_t length) {
	for (uint16_t i = 1; i < length; ++i){
		int32_t temp = A[i];
		uint16_t idx = i - 1;
		while (temp < A[idx]) {
			A[idx + 1] = A[idx];
			--idx;
		}
		A[idx + 1] = temp;
	}
}
```

## 选择排序

每次选择剩余元素中的一个最值，加入到已排好序的序列中

```c++
void SelectSort(int32_t* A, uint16_t length) {
	for (uint16_t i = 0; i < length; i++){
		int32_t min = i;
		for (uint16_t j = i + 1; j < length; j++) {
			min = A[min] > A[j] ? j : min;
		}
        swap(A[min],A[i]);
	}
}
```

## 冒泡排序

相邻元素对比，一轮冒出一个到头部

```c++
void BubbleSort(int32_t* A, uint16_t length) {
	for (uint16_t i = 0; i < length; i++){
		for (uint16_t j = i + 1; j < length; j++) {
			int32_t temp;
			if (A[i] > A[j]) {
				swap(A[i],A[j]);
			}
		}
	}
}
```

## 希尔排序

间隔排序，最后归并