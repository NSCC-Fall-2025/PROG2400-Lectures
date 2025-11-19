#include <iostream>
#include <iomanip>
#include <span>
#include <chrono>
#include <random>

using clk = std::chrono::high_resolution_clock;

void track_time(auto desc, void (*sort)(std::span<int>), std::span<int> nums) {
    auto t = clk::now();
    sort(nums);
    const std::chrono::duration<double> span = clk::now() - t;
    std::cout << std::setw(15) << desc << ": ";
    std::cout << "time " << span.count() << " s" << std::endl;
}

void fill_array(std::span<int> nums) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<size_t> dist(1, nums.size());
    std::generate(nums.begin(), nums.end(), [&]() {
        return dist(rng);
    });
}

void dump_array(std::span<int> arr) {
    for (auto i : arr) {
        std::cout << std::setw(3) << i;
    }
    std::cout << std::endl;
}

bool check_sort(const std::span<int> arr) {
    for (auto i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void bubble_sort(std::span<int> arr) {
    for (auto i = 0; i < arr.size() - 1; i++) {
        for (auto j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selection_sort(std::span<int> arr) {
    for (auto i = 0; i < arr.size() - 1; i++) {
        // find the smallest number
        auto lowest = i;
        for (auto j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[lowest]) {
                lowest = j;
            }
        }

        // put the lowest in the correct position
        if (arr[lowest] < arr[i]) {
            std::swap(arr[lowest], arr[i]);
        }
    }
}

void insertion_sort(std::span<int> arr) {
    for (auto i = 1; i < arr.size(); i++) {
        // pull out the card to examine
        const auto temp = arr[i];

        // shuffle any elements greater than the number to the right
        // to make room for the insertion
        auto j = i;
        for (; j > 0 && temp < arr[j - 1]; j--) {
            arr[j] = arr[j - 1];
        }

        // perform the insertion
        arr[j] = temp;
    }
}

void shell_sort(std::span<int> arr) {
    // create gaps, starting with half the array size
    for (auto gap = arr.size() / 2; gap > 0; gap /= 2) {
        // select the starting element to sort with
        for (auto start = 0; start < gap; start++) {
            // apply the insertion sort on the sub-array

            for (auto i = start + gap; i < arr.size(); i += gap) {
                // pull out the card to examine
                const auto temp = arr[i];

                // shuffle any elements greater than the number to the right
                // to make room for the insertion
                auto j = i;
                for (; j >= gap && temp < arr[j - gap]; j -= gap) {
                    arr[j] = arr[j - gap];
                }

                // perform the insertion
                arr[j] = temp;
            }
        }
    }
}

auto split(std::span<int> arr) {
    // choose a pivot point
    auto pivot = arr[0];

    // start searching for numbers less than and greater than the pivot
    auto left = 0;
    auto right = arr.size() - 1;

    // keep swapping until the left meets the right index
    while (left < right) {
        // search for an element less than the pivot
        while (right > 0 && pivot < arr[right]) right--;

        // search for an element greater than the pivot
        while (left < right && pivot >= arr[left]) left++;

        // if two were found out of place, swap them
        if (left < right && arr[left] != arr[right]) {
            std::swap(arr[left], arr[right]);
        }
    }

    // now move the pivot point to its new location
    arr[0] = arr[right];
    arr[right] = pivot;

    return right;
}

void quick_sort(std::span<int> arr) {
    // the array is sorted when it only has zero or one element
    if (arr.size() <= 1) return;

    // pick a "pivot" point and split into two sub-arrays
    // less than the pivot is moved to the left
    // greater than the pivot is moved to the right
    auto pivot = split(arr);

    // sort the left side
    quick_sort(arr.subspan(0, pivot));

    // sort the right side
    quick_sort(arr.subspan(pivot + 1, arr.size() - pivot - 1));
}

void heapify(std::span<int> arr, size_t i) {
    // assume the parent is the largest number in the tree
    auto largest = i;
    auto left = 2 * i + 1;
    auto right = 2 * i + 2;

    // is the left child larger than the parent?
    if (left < arr.size() && arr[left] > arr[largest])
        largest = left;

    // is the right child larger than the parent or the left child?
    if (right < arr.size() && arr[right] > arr[largest])
        largest = right;

    // swap the largest with the parent (if needed)
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, largest);
    }
}

void heap_sort(std::span<int> arr) {
    auto n = arr.size();

    // build the "max" heap structure
    // start at the last parent in the heap
    for (auto i = n / 2; i > 0; i--) {
        // move larger numbers to parent
        heapify(arr, i - 1);
    }

    // one by one extract elements in order
    for (auto i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr.subspan(0, i), 0);
    }
}

int main() {
    for (auto len = 10uz; len <= 1000000uz; len *= 10uz) {
        std::cout << "len = " << len << std::endl;

        auto nums = new int[len];

        // bubble sort
        //fill_array({nums, len});
        //track_time("bubble sort", bubble_sort, {nums, len});

        // selection sort
        //fill_array({nums, len});
        //track_time("selection sort", selection_sort, {nums, len});

        // insertion sort
        //fill_array({nums, len});
        //track_time("insertion sort", insertion_sort, {nums, len});

        // shell sort
        fill_array({nums, len});
        track_time("shell sort", shell_sort, {nums, len});

        // quick sort
        fill_array({nums, len});
        track_time("quick sort", quick_sort, {nums, len});

        // heap sort
        fill_array({nums, len});
        track_time("heap sort", heap_sort, {nums, len});

        if (check_sort({nums, len})) {
            std::cout << "SUCCESS!" << std::endl;
        } else {
            std::cout << "FAILURE!" << std::endl;
        }

        delete[] nums;
    }

    return 0;
}
