"""Exercise the line protocol against the compiled segmentation backend."""
import pathlib
import subprocess
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]


class Segmentation(unittest.TestCase):
    def test_empty_lines_and_unicode_lengths(self):
        dictionaries = ROOT / "cppjieba" / "dict"
        args = [str(ROOT / "cnws")] + [str(dictionaries / name) for name in (
            "jieba.dict.utf8", "hmm_model.utf8", "user.dict.utf8",
            "idf.utf8", "stop_words.utf8")]
        texts = ["", "\r", "中文分词", "ASCII", "é中文", "𠮷中文", "😀"]
        result = subprocess.run(args, input="\n".join(texts + ["EOF", "ignored"]) + "\n",
                                text=True, capture_output=True, timeout=20, check=True)
        lines = result.stdout.splitlines()[2:]
        self.assertEqual(len(lines), len(texts))
        for text, line in zip(texts, lines):
            with self.subTest(text=text):
                lengths = [int(value) for value in line.rsplit(":", 1)[1].split()]
                self.assertEqual(sum(lengths), len(text.rstrip("\r")))
                self.assertTrue(all(length > 0 for length in lengths))


if __name__ == "__main__":
    unittest.main()
