// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef COMPRESSED_IMAGE_H_
#define COMPRESSED_IMAGE_H_

#include <stddef.h>
#include <stdint.h>
#include <string>

#include "image.h"
#include "pik_info.h"
#include "quantizer.h"

namespace pik {

Image3F AlignImage(const Image3F& in, const size_t N);

void CenterOpsinValues(Image3F* img);

void YToBTransform(const float factor, Image3F* opsin);

typedef Image3W QuantizedCoeffs;

QuantizedCoeffs ComputeCoefficients(const Image3F& opsin,
                                    const Quantizer& quantizer);

std::string EncodeToBitstream(const QuantizedCoeffs& qcoeffs,
                              const Quantizer& quantizer,
                              int ytob,
                              bool fast_mode,
                              PikInfo* info);

bool DecodeFromBitstream(const uint8_t* data, const size_t data_size,
                         const size_t xsize, const size_t ysize,
                         int* ytob,
                         Quantizer* quantizer,
                         QuantizedCoeffs* qcoeffs,
                         size_t* compressed_size);

Image3F ReconOpsinImage(const QuantizedCoeffs& qcoeffs,
                        const Quantizer& quantizer);

}  // namespace pik

#endif  // COMPRESSED_IMAGE_H_
