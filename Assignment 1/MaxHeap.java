public class Assignment1 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MaxHeap heap = new MaxHeap(100);
		try {
			heap.DeleteMax();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
}

class MaxHeap {
	private int[] arr;
	private int sentinel1 = 0;
	private int sentinel2;
	private int arrayLength;
	private int currentSize = 0;
	/**
	 * Constructor to initialize the Heap
	 * @param n
	 */
	public MaxHeap(int n) {
		this.arr = new int[n];
		this.arr[0] = Integer.MAX_VALUE;
		this.sentinel2 = n-1;
		this.arr[sentinel2] = Integer.MIN_VALUE;
		this.arrayLength = n-2;
	}
	
	/**
	 * Returns the current size of the Heap. 
	 * The sentinel element is at 0, so the currentSize disregards the existence of sentinel
	 * @return
	 */
	public int CurrentSize() {
		return this.currentSize; 
	}
	
	/**
	 * Adds the number to Heap, and calls heapifyHeap so that the correct 
	 * Heap order is maintained
	 * @param number
	 * @throws HeapFullException 
	 */
	public void add(int number) throws HeapFullException {
		if(this.currentSize <= arrayLength) {
		int destinationIndex = this.currentSize ++;
		arr[destinationIndex] = number;
		heapifyHeap(destinationIndex);
		} else {
			throw new HeapFullException("Heap is full.");
		}
	}
	
	public void DeleteMax() throws NoElementException {
		if(this.currentSize > 0) {
			swap(1, this.currentSize);
			this.currentSize --;
			heapifyHeapDelete(1);
		} else {
			throw new NoElementException("Heap Empty.");
		}
	}
	
	/**
	 * Return the max element of the Heap
	 * @return
	 * @throws NoElementException 
	 */
	public int ReturnMax() throws NoElementException {
		if(this.currentSize > 0) {
			return arr[1];
		}
		throw new NoElementException("Heap Empty.");
	}
	
	/**
	 * Given the index of a node, return the parent index
	 * @param index
	 * @return
	 */
	private int parent(int index) {
		return Math.floorDiv(index, 2);
	}
	
	/**
	 * Given the index of a node, returns the index of the left child
	 * @param index
	 * @return
	 */
	private int leftChild(int index) {
		int leftIndex = (2*index <= this.currentSize) ? 2*index  : sentinel2;
		return leftIndex;
		 
	}
	
	/**
	 * Given the index of a node, returns the index of the right child
	 * @param index
	 * @return
	 */
	private int rightChild(int index) {
		int rightIndex = (2*index + 1 < this.currentSize) ? 2*index + 1 : sentinel2;
		return rightIndex;
	}
	
	/**
	 * If the property of the Heap is violated due to addition of a new element,
	 *  this function fixes the heap.
	 * @param index
	 */
	private void heapifyHeap(int index) {
		int parentIndex = parent(index);
		while (arr[index] > arr[parentIndex]) {
			swap(index, parentIndex);
			index = parentIndex;
			parentIndex = parent(index);
		}
	}
	
	/**
	 * If the property of the Heap is violated due to removal of an element,
	 *  this function fixes the heap.
	 *  
	 * @param index
	 */
	private void heapifyHeapDelete(int index) {
		int maxChildIndex = arr[leftChild(index)] > arr[rightChild(index)] 
				? leftChild(index) : rightChild(index);
		
		while (arr[index] > arr[maxChildIndex]) {
			swap(index, maxChildIndex);
			index = maxChildIndex;
			maxChildIndex = arr[leftChild(index)] > arr[rightChild(index)] 
					? leftChild(index) : rightChild(index);
		}
	}
	
	private void swap(int target, int destination) {
		int temp = arr[target];
		arr[target] = arr[destination];
		arr[destination] = temp;
	}
	
}
class NoElementException extends Exception {
    public NoElementException(String errorMessage)
    {
        // Call constructor of parent Exception
        super(errorMessage);
    }
}

class HeapFullException extends Exception {
    public HeapFullException(String errorMessage)
    {
        // Call constructor of parent Exception
        super(errorMessage);
    }
}
