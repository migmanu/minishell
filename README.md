![MISH](https://github.com/migmanu/minishell/assets/52668755/77ca9273-9cd4-40bc-a26d-40ee526e114f)

<h1 id="the-mish-project">The Mish Project</h1>
<p>Welcome to Mish: A Simple Bash Clone Developed for the 42 Berlin School Minishell Project.</p>
<p>Written by <a href="https://github.com/migmanu/">migmanu</a> and <a href="https://github.com/SebasNadu/">SebasNadu</a>
, in accordance with version number 7.1 of the subject. This project does not cover the bonus part. In total, it took us around four weeks to finish the whole thing.</p>
<picture>
    <img alt="minishell" src="https://github.com/SebasNadu/42_minishell/assets/98430438/fafa7b95-7df7-49a6-8f71-1c93415a1b28">
</picture>
<h2 id="installation">Installation</h2>
<p>To test our <code>minishell</code>, Mish, follow these steps on both Linux and macOS:</p>
<br>
<ol>
  <li><strong>Clone and build the repository:</strong></li>

```bash
git clone https://github.com/your-username/your-repo.git
cd your-repo
make
```

Wait until <code>libft</code> is cloned and built.

  <li><strong>Run Mish:</strong></li>
 <code>./minishell</code>
</ol>
<p>Now you're ready to explore Mish! If you encounter any issues or have questions, feel free to reach out to us.</p>
<h2 id="about-the-project">About the Project</h2>
<p>The <code>minishell</code> project requires students to develop a simple clone of Bash. It is also the first group project of the 42 Core Curriculum. From these two statements, we can easily identify the main challenges and goals of the task:</p>
<ul>
	<li>Acquire a deep understanding of Bash inner workings.</li>
	<li>Learn how lexical and syntactic analysis works, which is indispensable also for compilers, interpreters, and programming languages.</li>
	<li>Coordinate work with your teammate.</li>
</ul>
<p>We believe that without properly addressing and planning for these two challenges from the very beginning, <code>minishell</code> will quickly turn into what a lot of students call &quot;minihell.&quot;</p>
<h3 id="understanding-bash">Understanding Bash</h3>
<p>Released in 1989, Bash has by now acquired almost mythical status. It is a universal tool that every programmer should feel, at the very least, acquainted with, if not properly comfortable. Therefore, sources at your disposal are plenty. If you are a 42 student, we advise you to search Slack for resources provided by fellow students over the years. Be aware, the <code>minishell</code> subject has changed over time, so not all advice is relevant. </p>
<p>Here is a list of some of the most mentioned and useful links we found online:</p>

#### Repositories

- [Repo with cool explaination](https://github.com/maiadegraaf/minishell)
- [Evaluation sheet](https://github.com/wis-aerrajiy/school21-checklists/blob/update_minishell/ng_3_minishell.pdf)

#### How-to's / minishell specific articles

- [Minishell: Building a mini-bash (a @42 project)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218) | tutorial
- [List of edge cases to test for](https://docs.google.com/spreadsheets/d/1TDwyd-S0WBAXehgkrKQtBJ6zquQ4p6k7JfE5g3jICNA/edit#gid=0)
- [Another list of edge cases and expected behaviors](https://docs.google.com/spreadsheets/u/0/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/htmlview?lsrp=1#gid=0) | some are not expected by the project subject
- [High level explanation of the project](https://haglobah.github.io/Mastering-42/holy_graph/minishell.html) | has good sources
- [42 Slack chat about how to implement history](https://42born2code.slack.com/archives/CN9RHKQHW/p1654165861713979)

#### On the shell

- [Really in-depth video series explanation of how the shell works](https://www.youtube.com/playlist?list=PLFAC320731F539902) | watch at 1.25x
- [Shell (computing) - Wikipedia](<https://en.wikipedia.org/wiki/Shell_(computing)>)
- [Read-eval-print loop](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop) | Basic paradigm behind CLI
- [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) | Extensive explanation of a shell written in C++
- [Shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Write your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) | paper on how to write a shell which might apply better for a non-bonus minishell.
- [A lot of cool resources in one place.](https://minishell.simple.ink/)

#### On the allowed functions

- [General info from all the allowed functions (in Korean).](https://velog.io/@chez_bono/Minishell#%EA%B5%AC%ED%98%84%ED%95%B4%EC%95%BC-%ED%95%A0-%EB%B9%8C%ED%8A%B8%EC%9D%B8)

<p>In our experience, no amount of reading will actually prepare you for some of Bash&#39;s more obscure behaviors. And although a lot of them are out of the scope of the project, there&#39;s still plenty that needs to be considered, even if you do not go for the bonus. We encountered a lot of these difficult cases while testing our almost finished project. This is the most stressful way of discovering them. Luckily, by then our program was robust enough to withstand most of them.</p>
<p>Nevertheless, there are two available online spreadsheets that cover a huge amount of cases to test for. You can find them linked above. It's a good idea to go through most, if not all, of them at least once to test your <code>minishell</code>. Maybe a read before could avoid some issues down the line too. But <strong>be aware</strong>, a lot of the cases mentioned in these spreadsheets are out of scope, apply only for bonus or are outright wrong. Do not follow them blindly, but test each with Bash on your own.</p>

<h3 id="coordinating-teamwork">Coordinating Teamwork</h3>
<p>There was no great complexity regarding teamwork. Given the small size of the team and our generous time availability, we went through a simple workflow.</p>
<p>For this you must have a basic understanding of Git, its advantages and dangers. There are many, easy to find, resources online. We can recommend this [game](https://learngitbranching.js.org/) for a fun approach.</p>
</p>
<p>Each change or bug fix was done inside a branch of this repository, pushed, reviewd by the other author and merged. We could make this work because we communicated a lot, either through Slack or coding side by side.</p>
<p>Regardless of how you chose to organize work, you will need to communicate as much as possible and try to understand whats going on even inside the files you have not written.</p>
<h2 id="how-mish-works">How Mish Works</h2>
<p>After you&#39;ve read the listed sources, you'll learn that Bash is composed of four distinct parts: the <code>scanner</code> or lexical scanner, the <code>tokenizer</code>, the <code>expander</code>, the <code>tokens parser</code>,and the <code>executor</code>. Tokens are put into a tree, which is then executed in the appropriate order. This should probably be your layout if you are aiming for the bonus.</p>
<ul>
	<li>The <code>scanner</code>: In charge of reading through the inputed command. It deals with problems such as syntax</li>
	<li>The <code>tokenizer</code>: Divides the inputed command into tokens, basic units of execution. Some of this tokes we call <code>operators</code>, like the pipe symbol, <code>redirections</code>, or <code>words</code>, which can be commands and/or arguments</li>
	<li>The <code>expander</code>: Expands expresions included within <code>$()</code>, such as enviroment variables.</li>
	<li>The <code>parser</code>: Parses the tokens and create an AST (abstract syntax tree)</li>
	<li>The <code>executor</code>: Manages forks, calls to commads and built-in commands (like <code>cd</code>). Must be well design in order for the piping to work exactly as in bash. Pay attention to cases like <code>cat cat ls</code>. </li>
</ul>
<p>
<picture>
    <img alt="bash_flow" src="https://github.com/SebasNadu/42_minishell/assets/98430438/35b27643-572a-443b-b257-146652ff9b91" width="500">
</picture>
<sup><sub><small>Visualization by https://twitter.com/@_lrlna</small></sub></sup>

To this you obviously have to add the built-in commands the subject requires. These are:</p>

<ul>
	<li>cd</li>
	<li>echo</li>
	<li>pwd</li>
	<li>export</li>
	<li>unset</li>
	<li>env</li>
	<li>exit</li>
</ul>

<p>But things can be simplified if you choose not to do the bonus. Mish does not use a tree structure to create an AST; instead, it employs a list of commands. This structure not only encompasses the entire command created after parsing the tokens but also handles redirections. If you aim to develop a more sophisticated shell and complete the bonus, an AST is the way to go; otherwise, a simple list suffices for the task.</p>
<picture>
    <img alt="mish_flow" src="https://github.com/SebasNadu/42_minishell/assets/98430438/c697a355-89e3-4035-b880-11ddc4fc3824" width="800">
</picture>
</br>
</br>
<p>There are a lot of edge cases the initial parsing has to take into consideration. Those spreadsheets certainly came in handy. It was also challenging to design the correct behavior for pipes. Be especially attentive to blocking commands like <code>cat</code> and how they interact with different types of commands like <code>ls</code> or <code>head</code>. Pipes are a somewhat abstract concept, so a lot of trial and error went into solving this part</p>
<p>You might also notice that we used a hash map for storing the environment variables. Although this involved some extra work at the beginning, it ended up simplifying a lot of our work. It certainly saved us from bugs in some, unanticipated, edge-cases. Though it is certainly not necessary to develop a hash map, we highly recommend to try it out.</p>
<p>In the spirit of not spoiling the project for anyone, we are not gonna go into a detailed explanation of how Mish works. If you have any doubts or need help, you can reach us via Slack to <code>jmigoya-</code> and <code>johnavar</code> .</p>
