#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct TrieNode {
    int count;
    struct TrieNode* children[ALPHABET_SIZE];
};

struct Trie {
    struct TrieNode* root;
};

struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*) malloc(sizeof(struct TrieNode));
    node->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(struct Trie** ppTrie, char* word) {
    if (*ppTrie == NULL) {
        *ppTrie = (struct Trie*) malloc(sizeof(struct Trie));
        (*ppTrie)->root = createNode();
    }

    struct TrieNode* node = (*ppTrie)->root;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            node->children[index] = createNode();
        }
        node = node->children[index];
    }
    node->count++;
}

int numberOfOccurances(struct Trie* pTrie, char* word) {
    if (pTrie == NULL || pTrie->root == NULL) {
        return 0;
    }

    struct TrieNode* node = pTrie->root;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            return 0;
        }
        node = node->children[index];
    }
    return node->count;
}

void deallocateNode(struct TrieNode* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deallocateNode(node->children[i]);
    }

    free(node);
}

struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }

    deallocateNode(pTrie->root);
    free(pTrie);

    return NULL;
}

int main(void) {
    struct Trie* trie = NULL;

    // read the number of words in the dictionary
    int n;
    scanf("%d", &n);

    // parse line by line, and insert each word to the trie data structure
    char word[100];
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(&trie, word);
    }

    // check the number of occurrences for each word in the array
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }

    return 0;
}
