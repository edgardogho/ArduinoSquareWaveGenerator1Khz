/**
   This is a 2 channel square wave generator.
   The square wave is generated using Timer1 Output Compare
   set for CTC and toogle on Compare.
   The output pins are OCR1A (9) and OCR1B (10)
   The frequency control is done using a variable resistor.
   Each channel has 2 variable resistors (in order to preset 2
   different frequencies per channel) and a digital input is used
   to select which resistor sets the output frequency.

   This project is used to control 2 stepper motors and adjust their
   speed using the variable resistors.

   Output Frequency: 16Hz ~ 1024 Hz

   Channel 1 Output Pin = 9
   Channel 1 Fast/Slow Select pin = 2
   Channel 1 Fast Input Value = A0
   Channel 1 Slow Input Value = A1

   Channel 2 Output Pin = 10
   Channel 2 Fast/Slow Select Pin = 3
   Channel 2 Fast Input Value = A2
   Channel 2 Slow Input Value = A3


*/

// Create a lookup table for the timer values
const PROGMEM uint16_t LUT[] = {
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  62500, // 16 Hz
  58823, // 17 Hz
  55555, // 18 Hz
  52631, // 19 Hz
  50000, // 20 Hz
  47619, // 21 Hz
  45454, // 22 Hz
  43478, // 23 Hz
  41666, // 24 Hz
  40000, // 25 Hz
  38461, // 26 Hz
  37037, // 27 Hz
  35714, // 28 Hz
  34482, // 29 Hz
  33333, // 30 Hz
  32258, // 31 Hz
  31250, // 32 Hz
  30303, // 33 Hz
  29411, // 34 Hz
  28571, // 35 Hz
  27777, // 36 Hz
  27027, // 37 Hz
  26315, // 38 Hz
  25641, // 39 Hz
  25000, // 40 Hz
  24390, // 41 Hz
  23809, // 42 Hz
  23255, // 43 Hz
  22727, // 44 Hz
  22222, // 45 Hz
  21739, // 46 Hz
  21276, // 47 Hz
  20833, // 48 Hz
  20408, // 49 Hz
  20000, // 50 Hz
  19607, // 51 Hz
  19230, // 52 Hz
  18867, // 53 Hz
  18518, // 54 Hz
  18181, // 55 Hz
  17857, // 56 Hz
  17543, // 57 Hz
  17241, // 58 Hz
  16949, // 59 Hz
  16666, // 60 Hz
  16393, // 61 Hz
  16129, // 62 Hz
  15873, // 63 Hz
  15625, // 64 Hz
  15384, // 65 Hz
  15151, // 66 Hz
  14925, // 67 Hz
  14705, // 68 Hz
  14492, // 69 Hz
  14285, // 70 Hz
  14084, // 71 Hz
  13888, // 72 Hz
  13698, // 73 Hz
  13513, // 74 Hz
  13333, // 75 Hz
  13157, // 76 Hz
  12987, // 77 Hz
  12820, // 78 Hz
  12658, // 79 Hz
  12500, // 80 Hz
  12345, // 81 Hz
  12195, // 82 Hz
  12048, // 83 Hz
  11904, // 84 Hz
  11764, // 85 Hz
  11627, // 86 Hz
  11494, // 87 Hz
  11363, // 88 Hz
  11235, // 89 Hz
  11111, // 90 Hz
  10989, // 91 Hz
  10869, // 92 Hz
  10752, // 93 Hz
  10638, // 94 Hz
  10526, // 95 Hz
  10416, // 96 Hz
  10309, // 97 Hz
  10204, // 98 Hz
  10101, // 99 Hz
  10000, // 100 Hz
  9900, // 101 Hz
  9803, // 102 Hz
  9708, // 103 Hz
  9615, // 104 Hz
  9523, // 105 Hz
  9433, // 106 Hz
  9345, // 107 Hz
  9259, // 108 Hz
  9174, // 109 Hz
  9090, // 110 Hz
  9009, // 111 Hz
  8928, // 112 Hz
  8849, // 113 Hz
  8771, // 114 Hz
  8695, // 115 Hz
  8620, // 116 Hz
  8547, // 117 Hz
  8474, // 118 Hz
  8403, // 119 Hz
  8333, // 120 Hz
  8264, // 121 Hz
  8196, // 122 Hz
  8130, // 123 Hz
  8064, // 124 Hz
  8000, // 125 Hz
  7936, // 126 Hz
  7874, // 127 Hz
  7812, // 128 Hz
  7751, // 129 Hz
  7692, // 130 Hz
  7633, // 131 Hz
  7575, // 132 Hz
  7518, // 133 Hz
  7462, // 134 Hz
  7407, // 135 Hz
  7352, // 136 Hz
  7299, // 137 Hz
  7246, // 138 Hz
  7194, // 139 Hz
  7142, // 140 Hz
  7092, // 141 Hz
  7042, // 142 Hz
  6993, // 143 Hz
  6944, // 144 Hz
  6896, // 145 Hz
  6849, // 146 Hz
  6802, // 147 Hz
  6756, // 148 Hz
  6711, // 149 Hz
  6666, // 150 Hz
  6622, // 151 Hz
  6578, // 152 Hz
  6535, // 153 Hz
  6493, // 154 Hz
  6451, // 155 Hz
  6410, // 156 Hz
  6369, // 157 Hz
  6329, // 158 Hz
  6289, // 159 Hz
  6250, // 160 Hz
  6211, // 161 Hz
  6172, // 162 Hz
  6134, // 163 Hz
  6097, // 164 Hz
  6060, // 165 Hz
  6024, // 166 Hz
  5988, // 167 Hz
  5952, // 168 Hz
  5917, // 169 Hz
  5882, // 170 Hz
  5847, // 171 Hz
  5813, // 172 Hz
  5780, // 173 Hz
  5747, // 174 Hz
  5714, // 175 Hz
  5681, // 176 Hz
  5649, // 177 Hz
  5617, // 178 Hz
  5586, // 179 Hz
  5555, // 180 Hz
  5524, // 181 Hz
  5494, // 182 Hz
  5464, // 183 Hz
  5434, // 184 Hz
  5405, // 185 Hz
  5376, // 186 Hz
  5347, // 187 Hz
  5319, // 188 Hz
  5291, // 189 Hz
  5263, // 190 Hz
  5235, // 191 Hz
  5208, // 192 Hz
  5181, // 193 Hz
  5154, // 194 Hz
  5128, // 195 Hz
  5102, // 196 Hz
  5076, // 197 Hz
  5050, // 198 Hz
  5025, // 199 Hz
  5000, // 200 Hz
  4975, // 201 Hz
  4950, // 202 Hz
  4926, // 203 Hz
  4901, // 204 Hz
  4878, // 205 Hz
  4854, // 206 Hz
  4830, // 207 Hz
  4807, // 208 Hz
  4784, // 209 Hz
  4761, // 210 Hz
  4739, // 211 Hz
  4716, // 212 Hz
  4694, // 213 Hz
  4672, // 214 Hz
  4651, // 215 Hz
  4629, // 216 Hz
  4608, // 217 Hz
  4587, // 218 Hz
  4566, // 219 Hz
  4545, // 220 Hz
  4524, // 221 Hz
  4504, // 222 Hz
  4484, // 223 Hz
  4464, // 224 Hz
  4444, // 225 Hz
  4424, // 226 Hz
  4405, // 227 Hz
  4385, // 228 Hz
  4366, // 229 Hz
  4347, // 230 Hz
  4329, // 231 Hz
  4310, // 232 Hz
  4291, // 233 Hz
  4273, // 234 Hz
  4255, // 235 Hz
  4237, // 236 Hz
  4219, // 237 Hz
  4201, // 238 Hz
  4184, // 239 Hz
  4166, // 240 Hz
  4149, // 241 Hz
  4132, // 242 Hz
  4115, // 243 Hz
  4098, // 244 Hz
  4081, // 245 Hz
  4065, // 246 Hz
  4048, // 247 Hz
  4032, // 248 Hz
  4016, // 249 Hz
  4000, // 250 Hz
  3984, // 251 Hz
  3968, // 252 Hz
  3952, // 253 Hz
  3937, // 254 Hz
  3921, // 255 Hz
  3906, // 256 Hz
  3891, // 257 Hz
  3875, // 258 Hz
  3861, // 259 Hz
  3846, // 260 Hz
  3831, // 261 Hz
  3816, // 262 Hz
  3802, // 263 Hz
  3787, // 264 Hz
  3773, // 265 Hz
  3759, // 266 Hz
  3745, // 267 Hz
  3731, // 268 Hz
  3717, // 269 Hz
  3703, // 270 Hz
  3690, // 271 Hz
  3676, // 272 Hz
  3663, // 273 Hz
  3649, // 274 Hz
  3636, // 275 Hz
  3623, // 276 Hz
  3610, // 277 Hz
  3597, // 278 Hz
  3584, // 279 Hz
  3571, // 280 Hz
  3558, // 281 Hz
  3546, // 282 Hz
  3533, // 283 Hz
  3521, // 284 Hz
  3508, // 285 Hz
  3496, // 286 Hz
  3484, // 287 Hz
  3472, // 288 Hz
  3460, // 289 Hz
  3448, // 290 Hz
  3436, // 291 Hz
  3424, // 292 Hz
  3412, // 293 Hz
  3401, // 294 Hz
  3389, // 295 Hz
  3378, // 296 Hz
  3367, // 297 Hz
  3355, // 298 Hz
  3344, // 299 Hz
  3333, // 300 Hz
  3322, // 301 Hz
  3311, // 302 Hz
  3300, // 303 Hz
  3289, // 304 Hz
  3278, // 305 Hz
  3267, // 306 Hz
  3257, // 307 Hz
  3246, // 308 Hz
  3236, // 309 Hz
  3225, // 310 Hz
  3215, // 311 Hz
  3205, // 312 Hz
  3194, // 313 Hz
  3184, // 314 Hz
  3174, // 315 Hz
  3164, // 316 Hz
  3154, // 317 Hz
  3144, // 318 Hz
  3134, // 319 Hz
  3125, // 320 Hz
  3115, // 321 Hz
  3105, // 322 Hz
  3095, // 323 Hz
  3086, // 324 Hz
  3076, // 325 Hz
  3067, // 326 Hz
  3058, // 327 Hz
  3048, // 328 Hz
  3039, // 329 Hz
  3030, // 330 Hz
  3021, // 331 Hz
  3012, // 332 Hz
  3003, // 333 Hz
  2994, // 334 Hz
  2985, // 335 Hz
  2976, // 336 Hz
  2967, // 337 Hz
  2958, // 338 Hz
  2949, // 339 Hz
  2941, // 340 Hz
  2932, // 341 Hz
  2923, // 342 Hz
  2915, // 343 Hz
  2906, // 344 Hz
  2898, // 345 Hz
  2890, // 346 Hz
  2881, // 347 Hz
  2873, // 348 Hz
  2865, // 349 Hz
  2857, // 350 Hz
  2849, // 351 Hz
  2840, // 352 Hz
  2832, // 353 Hz
  2824, // 354 Hz
  2816, // 355 Hz
  2808, // 356 Hz
  2801, // 357 Hz
  2793, // 358 Hz
  2785, // 359 Hz
  2777, // 360 Hz
  2770, // 361 Hz
  2762, // 362 Hz
  2754, // 363 Hz
  2747, // 364 Hz
  2739, // 365 Hz
  2732, // 366 Hz
  2724, // 367 Hz
  2717, // 368 Hz
  2710, // 369 Hz
  2702, // 370 Hz
  2695, // 371 Hz
  2688, // 372 Hz
  2680, // 373 Hz
  2673, // 374 Hz
  2666, // 375 Hz
  2659, // 376 Hz
  2652, // 377 Hz
  2645, // 378 Hz
  2638, // 379 Hz
  2631, // 380 Hz
  2624, // 381 Hz
  2617, // 382 Hz
  2610, // 383 Hz
  2604, // 384 Hz
  2597, // 385 Hz
  2590, // 386 Hz
  2583, // 387 Hz
  2577, // 388 Hz
  2570, // 389 Hz
  2564, // 390 Hz
  2557, // 391 Hz
  2551, // 392 Hz
  2544, // 393 Hz
  2538, // 394 Hz
  2531, // 395 Hz
  2525, // 396 Hz
  2518, // 397 Hz
  2512, // 398 Hz
  2506, // 399 Hz
  2500, // 400 Hz
  2493, // 401 Hz
  2487, // 402 Hz
  2481, // 403 Hz
  2475, // 404 Hz
  2469, // 405 Hz
  2463, // 406 Hz
  2457, // 407 Hz
  2450, // 408 Hz
  2444, // 409 Hz
  2439, // 410 Hz
  2433, // 411 Hz
  2427, // 412 Hz
  2421, // 413 Hz
  2415, // 414 Hz
  2409, // 415 Hz
  2403, // 416 Hz
  2398, // 417 Hz
  2392, // 418 Hz
  2386, // 419 Hz
  2380, // 420 Hz
  2375, // 421 Hz
  2369, // 422 Hz
  2364, // 423 Hz
  2358, // 424 Hz
  2352, // 425 Hz
  2347, // 426 Hz
  2341, // 427 Hz
  2336, // 428 Hz
  2331, // 429 Hz
  2325, // 430 Hz
  2320, // 431 Hz
  2314, // 432 Hz
  2309, // 433 Hz
  2304, // 434 Hz
  2298, // 435 Hz
  2293, // 436 Hz
  2288, // 437 Hz
  2283, // 438 Hz
  2277, // 439 Hz
  2272, // 440 Hz
  2267, // 441 Hz
  2262, // 442 Hz
  2257, // 443 Hz
  2252, // 444 Hz
  2247, // 445 Hz
  2242, // 446 Hz
  2237, // 447 Hz
  2232, // 448 Hz
  2227, // 449 Hz
  2222, // 450 Hz
  2217, // 451 Hz
  2212, // 452 Hz
  2207, // 453 Hz
  2202, // 454 Hz
  2197, // 455 Hz
  2192, // 456 Hz
  2188, // 457 Hz
  2183, // 458 Hz
  2178, // 459 Hz
  2173, // 460 Hz
  2169, // 461 Hz
  2164, // 462 Hz
  2159, // 463 Hz
  2155, // 464 Hz
  2150, // 465 Hz
  2145, // 466 Hz
  2141, // 467 Hz
  2136, // 468 Hz
  2132, // 469 Hz
  2127, // 470 Hz
  2123, // 471 Hz
  2118, // 472 Hz
  2114, // 473 Hz
  2109, // 474 Hz
  2105, // 475 Hz
  2100, // 476 Hz
  2096, // 477 Hz
  2092, // 478 Hz
  2087, // 479 Hz
  2083, // 480 Hz
  2079, // 481 Hz
  2074, // 482 Hz
  2070, // 483 Hz
  2066, // 484 Hz
  2061, // 485 Hz
  2057, // 486 Hz
  2053, // 487 Hz
  2049, // 488 Hz
  2044, // 489 Hz
  2040, // 490 Hz
  2036, // 491 Hz
  2032, // 492 Hz
  2028, // 493 Hz
  2024, // 494 Hz
  2020, // 495 Hz
  2016, // 496 Hz
  2012, // 497 Hz
  2008, // 498 Hz
  2004, // 499 Hz
  2000, // 500 Hz
  1996, // 501 Hz
  1992, // 502 Hz
  1988, // 503 Hz
  1984, // 504 Hz
  1980, // 505 Hz
  1976, // 506 Hz
  1972, // 507 Hz
  1968, // 508 Hz
  1964, // 509 Hz
  1960, // 510 Hz
  1956, // 511 Hz
  1953, // 512 Hz
  1949, // 513 Hz
  1945, // 514 Hz
  1941, // 515 Hz
  1937, // 516 Hz
  1934, // 517 Hz
  1930, // 518 Hz
  1926, // 519 Hz
  1923, // 520 Hz
  1919, // 521 Hz
  1915, // 522 Hz
  1912, // 523 Hz
  1908, // 524 Hz
  1904, // 525 Hz
  1901, // 526 Hz
  1897, // 527 Hz
  1893, // 528 Hz
  1890, // 529 Hz
  1886, // 530 Hz
  1883, // 531 Hz
  1879, // 532 Hz
  1876, // 533 Hz
  1872, // 534 Hz
  1869, // 535 Hz
  1865, // 536 Hz
  1862, // 537 Hz
  1858, // 538 Hz
  1855, // 539 Hz
  1851, // 540 Hz
  1848, // 541 Hz
  1845, // 542 Hz
  1841, // 543 Hz
  1838, // 544 Hz
  1834, // 545 Hz
  1831, // 546 Hz
  1828, // 547 Hz
  1824, // 548 Hz
  1821, // 549 Hz
  1818, // 550 Hz
  1814, // 551 Hz
  1811, // 552 Hz
  1808, // 553 Hz
  1805, // 554 Hz
  1801, // 555 Hz
  1798, // 556 Hz
  1795, // 557 Hz
  1792, // 558 Hz
  1788, // 559 Hz
  1785, // 560 Hz
  1782, // 561 Hz
  1779, // 562 Hz
  1776, // 563 Hz
  1773, // 564 Hz
  1769, // 565 Hz
  1766, // 566 Hz
  1763, // 567 Hz
  1760, // 568 Hz
  1757, // 569 Hz
  1754, // 570 Hz
  1751, // 571 Hz
  1748, // 572 Hz
  1745, // 573 Hz
  1742, // 574 Hz
  1739, // 575 Hz
  1736, // 576 Hz
  1733, // 577 Hz
  1730, // 578 Hz
  1727, // 579 Hz
  1724, // 580 Hz
  1721, // 581 Hz
  1718, // 582 Hz
  1715, // 583 Hz
  1712, // 584 Hz
  1709, // 585 Hz
  1706, // 586 Hz
  1703, // 587 Hz
  1700, // 588 Hz
  1697, // 589 Hz
  1694, // 590 Hz
  1692, // 591 Hz
  1689, // 592 Hz
  1686, // 593 Hz
  1683, // 594 Hz
  1680, // 595 Hz
  1677, // 596 Hz
  1675, // 597 Hz
  1672, // 598 Hz
  1669, // 599 Hz
  1666, // 600 Hz
  1663, // 601 Hz
  1661, // 602 Hz
  1658, // 603 Hz
  1655, // 604 Hz
  1652, // 605 Hz
  1650, // 606 Hz
  1647, // 607 Hz
  1644, // 608 Hz
  1642, // 609 Hz
  1639, // 610 Hz
  1636, // 611 Hz
  1633, // 612 Hz
  1631, // 613 Hz
  1628, // 614 Hz
  1626, // 615 Hz
  1623, // 616 Hz
  1620, // 617 Hz
  1618, // 618 Hz
  1615, // 619 Hz
  1612, // 620 Hz
  1610, // 621 Hz
  1607, // 622 Hz
  1605, // 623 Hz
  1602, // 624 Hz
  1600, // 625 Hz
  1597, // 626 Hz
  1594, // 627 Hz
  1592, // 628 Hz
  1589, // 629 Hz
  1587, // 630 Hz
  1584, // 631 Hz
  1582, // 632 Hz
  1579, // 633 Hz
  1577, // 634 Hz
  1574, // 635 Hz
  1572, // 636 Hz
  1569, // 637 Hz
  1567, // 638 Hz
  1564, // 639 Hz
  1562, // 640 Hz
  1560, // 641 Hz
  1557, // 642 Hz
  1555, // 643 Hz
  1552, // 644 Hz
  1550, // 645 Hz
  1547, // 646 Hz
  1545, // 647 Hz
  1543, // 648 Hz
  1540, // 649 Hz
  1538, // 650 Hz
  1536, // 651 Hz
  1533, // 652 Hz
  1531, // 653 Hz
  1529, // 654 Hz
  1526, // 655 Hz
  1524, // 656 Hz
  1522, // 657 Hz
  1519, // 658 Hz
  1517, // 659 Hz
  1515, // 660 Hz
  1512, // 661 Hz
  1510, // 662 Hz
  1508, // 663 Hz
  1506, // 664 Hz
  1503, // 665 Hz
  1501, // 666 Hz
  1499, // 667 Hz
  1497, // 668 Hz
  1494, // 669 Hz
  1492, // 670 Hz
  1490, // 671 Hz
  1488, // 672 Hz
  1485, // 673 Hz
  1483, // 674 Hz
  1481, // 675 Hz
  1479, // 676 Hz
  1477, // 677 Hz
  1474, // 678 Hz
  1472, // 679 Hz
  1470, // 680 Hz
  1468, // 681 Hz
  1466, // 682 Hz
  1464, // 683 Hz
  1461, // 684 Hz
  1459, // 685 Hz
  1457, // 686 Hz
  1455, // 687 Hz
  1453, // 688 Hz
  1451, // 689 Hz
  1449, // 690 Hz
  1447, // 691 Hz
  1445, // 692 Hz
  1443, // 693 Hz
  1440, // 694 Hz
  1438, // 695 Hz
  1436, // 696 Hz
  1434, // 697 Hz
  1432, // 698 Hz
  1430, // 699 Hz
  1428, // 700 Hz
  1426, // 701 Hz
  1424, // 702 Hz
  1422, // 703 Hz
  1420, // 704 Hz
  1418, // 705 Hz
  1416, // 706 Hz
  1414, // 707 Hz
  1412, // 708 Hz
  1410, // 709 Hz
  1408, // 710 Hz
  1406, // 711 Hz
  1404, // 712 Hz
  1402, // 713 Hz
  1400, // 714 Hz
  1398, // 715 Hz
  1396, // 716 Hz
  1394, // 717 Hz
  1392, // 718 Hz
  1390, // 719 Hz
  1388, // 720 Hz
  1386, // 721 Hz
  1385, // 722 Hz
  1383, // 723 Hz
  1381, // 724 Hz
  1379, // 725 Hz
  1377, // 726 Hz
  1375, // 727 Hz
  1373, // 728 Hz
  1371, // 729 Hz
  1369, // 730 Hz
  1367, // 731 Hz
  1366, // 732 Hz
  1364, // 733 Hz
  1362, // 734 Hz
  1360, // 735 Hz
  1358, // 736 Hz
  1356, // 737 Hz
  1355, // 738 Hz
  1353, // 739 Hz
  1351, // 740 Hz
  1349, // 741 Hz
  1347, // 742 Hz
  1345, // 743 Hz
  1344, // 744 Hz
  1342, // 745 Hz
  1340, // 746 Hz
  1338, // 747 Hz
  1336, // 748 Hz
  1335, // 749 Hz
  1333, // 750 Hz
  1331, // 751 Hz
  1329, // 752 Hz
  1328, // 753 Hz
  1326, // 754 Hz
  1324, // 755 Hz
  1322, // 756 Hz
  1321, // 757 Hz
  1319, // 758 Hz
  1317, // 759 Hz
  1315, // 760 Hz
  1314, // 761 Hz
  1312, // 762 Hz
  1310, // 763 Hz
  1308, // 764 Hz
  1307, // 765 Hz
  1305, // 766 Hz
  1303, // 767 Hz
  1302, // 768 Hz
  1300, // 769 Hz
  1298, // 770 Hz
  1297, // 771 Hz
  1295, // 772 Hz
  1293, // 773 Hz
  1291, // 774 Hz
  1290, // 775 Hz
  1288, // 776 Hz
  1287, // 777 Hz
  1285, // 778 Hz
  1283, // 779 Hz
  1282, // 780 Hz
  1280, // 781 Hz
  1278, // 782 Hz
  1277, // 783 Hz
  1275, // 784 Hz
  1273, // 785 Hz
  1272, // 786 Hz
  1270, // 787 Hz
  1269, // 788 Hz
  1267, // 789 Hz
  1265, // 790 Hz
  1264, // 791 Hz
  1262, // 792 Hz
  1261, // 793 Hz
  1259, // 794 Hz
  1257, // 795 Hz
  1256, // 796 Hz
  1254, // 797 Hz
  1253, // 798 Hz
  1251, // 799 Hz
  1250, // 800 Hz
  1248, // 801 Hz
  1246, // 802 Hz
  1245, // 803 Hz
  1243, // 804 Hz
  1242, // 805 Hz
  1240, // 806 Hz
  1239, // 807 Hz
  1237, // 808 Hz
  1236, // 809 Hz
  1234, // 810 Hz
  1233, // 811 Hz
  1231, // 812 Hz
  1230, // 813 Hz
  1228, // 814 Hz
  1226, // 815 Hz
  1225, // 816 Hz
  1223, // 817 Hz
  1222, // 818 Hz
  1221, // 819 Hz
  1219, // 820 Hz
  1218, // 821 Hz
  1216, // 822 Hz
  1215, // 823 Hz
  1213, // 824 Hz
  1212, // 825 Hz
  1210, // 826 Hz
  1209, // 827 Hz
  1207, // 828 Hz
  1206, // 829 Hz
  1204, // 830 Hz
  1203, // 831 Hz
  1201, // 832 Hz
  1200, // 833 Hz
  1199, // 834 Hz
  1197, // 835 Hz
  1196, // 836 Hz
  1194, // 837 Hz
  1193, // 838 Hz
  1191, // 839 Hz
  1190, // 840 Hz
  1189, // 841 Hz
  1187, // 842 Hz
  1186, // 843 Hz
  1184, // 844 Hz
  1183, // 845 Hz
  1182, // 846 Hz
  1180, // 847 Hz
  1179, // 848 Hz
  1177, // 849 Hz
  1176, // 850 Hz
  1175, // 851 Hz
  1173, // 852 Hz
  1172, // 853 Hz
  1170, // 854 Hz
  1169, // 855 Hz
  1168, // 856 Hz
  1166, // 857 Hz
  1165, // 858 Hz
  1164, // 859 Hz
  1162, // 860 Hz
  1161, // 861 Hz
  1160, // 862 Hz
  1158, // 863 Hz
  1157, // 864 Hz
  1156, // 865 Hz
  1154, // 866 Hz
  1153, // 867 Hz
  1152, // 868 Hz
  1150, // 869 Hz
  1149, // 870 Hz
  1148, // 871 Hz
  1146, // 872 Hz
  1145, // 873 Hz
  1144, // 874 Hz
  1142, // 875 Hz
  1141, // 876 Hz
  1140, // 877 Hz
  1138, // 878 Hz
  1137, // 879 Hz
  1136, // 880 Hz
  1135, // 881 Hz
  1133, // 882 Hz
  1132, // 883 Hz
  1131, // 884 Hz
  1129, // 885 Hz
  1128, // 886 Hz
  1127, // 887 Hz
  1126, // 888 Hz
  1124, // 889 Hz
  1123, // 890 Hz
  1122, // 891 Hz
  1121, // 892 Hz
  1119, // 893 Hz
  1118, // 894 Hz
  1117, // 895 Hz
  1116, // 896 Hz
  1114, // 897 Hz
  1113, // 898 Hz
  1112, // 899 Hz
  1111, // 900 Hz
  1109, // 901 Hz
  1108, // 902 Hz
  1107, // 903 Hz
  1106, // 904 Hz
  1104, // 905 Hz
  1103, // 906 Hz
  1102, // 907 Hz
  1101, // 908 Hz
  1100, // 909 Hz
  1098, // 910 Hz
  1097, // 911 Hz
  1096, // 912 Hz
  1095, // 913 Hz
  1094, // 914 Hz
  1092, // 915 Hz
  1091, // 916 Hz
  1090, // 917 Hz
  1089, // 918 Hz
  1088, // 919 Hz
  1086, // 920 Hz
  1085, // 921 Hz
  1084, // 922 Hz
  1083, // 923 Hz
  1082, // 924 Hz
  1081, // 925 Hz
  1079, // 926 Hz
  1078, // 927 Hz
  1077, // 928 Hz
  1076, // 929 Hz
  1075, // 930 Hz
  1074, // 931 Hz
  1072, // 932 Hz
  1071, // 933 Hz
  1070, // 934 Hz
  1069, // 935 Hz
  1068, // 936 Hz
  1067, // 937 Hz
  1066, // 938 Hz
  1064, // 939 Hz
  1063, // 940 Hz
  1062, // 941 Hz
  1061, // 942 Hz
  1060, // 943 Hz
  1059, // 944 Hz
  1058, // 945 Hz
  1057, // 946 Hz
  1055, // 947 Hz
  1054, // 948 Hz
  1053, // 949 Hz
  1052, // 950 Hz
  1051, // 951 Hz
  1050, // 952 Hz
  1049, // 953 Hz
  1048, // 954 Hz
  1047, // 955 Hz
  1046, // 956 Hz
  1044, // 957 Hz
  1043, // 958 Hz
  1042, // 959 Hz
  1041, // 960 Hz
  1040, // 961 Hz
  1039, // 962 Hz
  1038, // 963 Hz
  1037, // 964 Hz
  1036, // 965 Hz
  1035, // 966 Hz
  1034, // 967 Hz
  1033, // 968 Hz
  1031, // 969 Hz
  1030, // 970 Hz
  1029, // 971 Hz
  1028, // 972 Hz
  1027, // 973 Hz
  1026, // 974 Hz
  1025, // 975 Hz
  1024, // 976 Hz
  1023, // 977 Hz
  1022, // 978 Hz
  1021, // 979 Hz
  1020, // 980 Hz
  1019, // 981 Hz
  1018, // 982 Hz
  1017, // 983 Hz
  1016, // 984 Hz
  1015, // 985 Hz
  1014, // 986 Hz
  1013, // 987 Hz
  1012, // 988 Hz
  1011, // 989 Hz
  1010, // 990 Hz
  1009, // 991 Hz
  1008, // 992 Hz
  1007, // 993 Hz
  1006, // 994 Hz
  1005, // 995 Hz
  1004, // 996 Hz
  1003, // 997 Hz
  1002, // 998 Hz
  1001, // 999 Hz
  1000, // 1000 Hz
  999, // 1001 Hz
  998, // 1002 Hz
  997, // 1003 Hz
  996, // 1004 Hz
  995, // 1005 Hz
  994, // 1006 Hz
  993, // 1007 Hz
  992, // 1008 Hz
  991, // 1009 Hz
  990, // 1010 Hz
  989, // 1011 Hz
  988, // 1012 Hz
  987, // 1013 Hz
  986, // 1014 Hz
  985, // 1015 Hz
  984, // 1016 Hz
  983, // 1017 Hz
  982, // 1018 Hz
  981, // 1019 Hz
  980, // 1020 Hz
  979, // 1021 Hz
  978, // 1022 Hz
  977, // 1023 Hz
  976  // 1024 Hz
};

//Declare global variables
int channel1Counter = 976;
int channel1Freq = 1023;
const uint8_t OC1A = 9;
const uint8_t sense1Fast = A0;
const uint8_t sense1Slow = A1;
const uint8_t fast1Select = 2;

int channel2Counter = 976;
int channel2Freq = 1023;
const uint8_t OC1B = 10;
const uint8_t sense2Fast = A2;
const uint8_t sense2Slow = A3;
const uint8_t fast2Select = 3;


void setup() {
  // Disable interrupts while seting up the timers
  cli();

  // Setup pins DDR 
  //  Output SquareWave pins
  pinMode(OC1A,  OUTPUT);
  pinMode(OC1B, OUTPUT);
  //  Input variable resistor
  pinMode(sense1Fast, INPUT);
  pinMode(sense1Slow, INPUT);
  pinMode(sense2Fast, INPUT);
  pinMode(sense2Slow, INPUT);
  //  Input Fast/Slow switch ping
  pinMode(fast1Select, INPUT_PULLUP);
  pinMode(fast2Select, INPUT_PULLUP);


  // Setup timer 1 values
  TCCR1A = TCCR1B = TCNT1= 0;//Clean registers
  OCR1A = channel1Counter;
  // Setup Toogle on OC1A/OC1B compare match
  TCCR1A |= (1 << COM1A0) | (1 << COM1B0); 
  // Setup the prescaler to divide by 8
  TCCR1B |= (1 << CS11); 
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);

  //Start interrupts
  sei();

}

//Interrupt Service Routine for Timer1 Compare A
//  When this interrupt happens the timer toogles OC1A,
//  but we can't reset the timer, since its also counting
//  for the second channel, so we need increment the compare
//  register 
ISR(TIMER1_COMPA_vect) { 
  //Bump the compare register
  OCR1A = OCR1A + channel1Counter;
}

//Interrupt Service Routine for Timer1 Compare B
//  When this interrupt happens the timer toogles OC1B,
//  but we can't reset the timer, since its also counting
//  for the first channel, so we need increment the compare
//  register 
ISR(TIMER1_COMPB_vect) { 
  //Bump the compare register
  OCR1B = OCR1B + channel2Counter;
}

void loop() {

  
  // Channel 1 read variable resistor depending on 
  // Fast/Slow select pin
  if (digitalRead(fast1Select) == HIGH)
    channel1Freq = analogRead(sense1Fast)/2;
  else
    channel1Freq = analogRead(sense1Slow)/2;

  //Values were divided by 2 so ignore least significant bit
  //returned by the ADC since it tends to oscillate a lot, so
  //Adjust by multiplying by 2. This basically makes half of the
  //LUT useless, but since the idea is to receive the frequencies
  //using the serial port I leave the full table.
  channel1Freq *=2; 
  if (channel1Freq>1024){
    channel1Freq = 1024;
  }
  // Pickup from the lut the timer value for the selected frequency
  channel1Counter = pgm_read_word_near(LUT + channel1Freq);


  //Channel 2 is pretty much the same as channel 1
   if (digitalRead(fast2Select) == HIGH)
    channel2Freq = analogRead(sense2Fast)/2;
  else
    channel2Freq = analogRead(sense2Slow)/2;

  //Values were divided by 2 so ignore least significant bit
  //returned by the ADC since it tends to oscillate a lot, so
  //Adjust by multiplying by 2. This basically makes half of the
  //LUT useless, but since the idea is to receive the frequencies
  //using the serial port I leave the full table.
  channel2Freq *=2; 
  if (channel2Freq>1024){
    channel2Freq = 1024;
  }
  // Pickup from the lut the timer value for the selected frequency
  channel2Counter = pgm_read_word_near(LUT + channel2Freq);

}
