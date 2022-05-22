// Copyright 2022 Vorobyova Anya

#include "../../../modules/task_4/vorobyova_a_gauss_horizontal/gauss_horizontal.h"

#include <omp.h>

#include <random>

#include "../../../3rdparty/unapproved/unapproved.h"

img getRandomImage(int width, int height) {
  std::random_device dev;
  static std::mt19937 gen(dev());
  std::uniform_int_distribution<> uid(0, 255);

  img image = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = uid(gen);
    }
  }

  return image;
}

float calcNewPixelColor(const img& image, int x, int y) {
  float returnC = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int idx = (i + 1) * kernel.size + j + 1;
      int pixel = image[y + i][x + j];
      returnC += pixel * kernel.data[idx];
    }
  }
  return returnC;
}

img getGauss(const img& image, int width, int height) {
  img new_image =
      std::vector<std::vector<int>>(height - 2, std::vector<int>(width - 2, 0));

  for (int i = 1; i < height - 1; i++) {
    for (int j = 1; j < width - 1; j++) {
      new_image[i - 1][j - 1] = calcNewPixelColor(image, j, i);
    }
  }
  return new_image;
}

img getGaussSTD(const img& image, int width, int height) {
  img new_image =
      std::vector<std::vector<int>>(height - 2, std::vector<int>(width - 2, 0));

  const int thread_num = std::thread::hardware_concurrency();

  auto thread_func = [width, &new_image, &image](int begin, int end,
                                                 int index) {
    for (int i = begin; i < end; i++) {
      for (int j = 1; j < width - 1; j++) {
        new_image[i - 1][j - 1] = calcNewPixelColor(image, j, i);
      }
    }
  };

  std::vector<std::thread> threads(thread_num);
  int delta = (height - 2) / thread_num;

  for (int thread = 0; thread < thread_num; ++thread) {
    int begin = delta * thread + 1;
    int end = delta * (thread + 1) + 1;

    if (thread != thread_num - 1) {
      threads[thread] = std::thread(thread_func, begin, end, thread);
    } else {
      threads[thread] = std::thread(thread_func, delta * (thread_num - 1) + 1,
                                    height - 1, thread_num - 1);
    }
  }

  for (auto&& i : threads) {
    i.join();
  }

  return new_image;
}
